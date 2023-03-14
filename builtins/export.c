/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:04 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/14 15:23:06 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../minishell.h"
#include "../env/env.h"

static int	list_len(char **list)
{
	int		i;

	i = 0;
	while (list[i] != NULL)
		i++;
	return (i);
}

static int	add_env_var(t_minishell *mini, char *var)
{
	char	**new_env_copy;
	int		i;

	new_env_copy
		= (char **)malloc(sizeof(char *) * (list_len(mini->env_copy) + 2));
	if (new_env_copy == NULL)
		return (ERROR);
	i = 0;
	while (mini->env_copy[i])
	{
		new_env_copy[i] = mini->env_copy[i];
		i++;
	}
	new_env_copy[i] = var;
	new_env_copy[i + 1] = NULL;
	free(mini->env_copy);
	mini->env_copy = new_env_copy;
	return (SUCCESS);
}

int	check_invalid_identifier(char *argu)
{
	int	i;

	i = 0;
	while (argu[i] && argu[i] != '=' && ft_isalnum(argu[i]))
		i++;
	if (ft_isalnum(argu[i]) == 0)
	{
		ft_putendl_fd(STR"minishell: export: not a valid identifier\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	check_var_name(char *var)
{
	int	len;

	len = ft_strlen(var);
	if (len == 1)
	{
		if (ft_isdigit(var[0]) != 0)
		{
			ft_putendl_fd(STR"minishell: export: not a valid identifier\n", 2);
			return (ERROR);
		}
		if (var[0] == '_')
			return (3);
	}
	else
	{
		if (check_invalid_identifier(var) == ERROR)
			return (ERROR);
		if (var[0] == '_' && var[1] == '=')
			return (3);
	}
	return (SUCCESS);
}

int	export_(t_minishell *minishell, char **argv)
{
	char	*var;
	int		tmp_int;

	if (argv[1] == NULL)
		return (print_all_env(minishell));
	tmp_int = check_var_name(argv[1]);
	if (tmp_int == ERROR)
		return (ERROR);
	if (tmp_int == 3 || ft_strchr(argv[1], '=') == 0)
		return (SUCCESS);
	var = ft_strdup(argv[1]);
	if (var == NULL)
		return (ERROR);
	tmp_int = get_env_var_index((const char **)minishell->env_copy, var);
	if (tmp_int == -1 && add_env_var(minishell, var) == ERROR)
	{
		free(var);
		return (ERROR);
	}
	else
	{
		free(minishell->env_copy[tmp_int]);
		minishell->env_copy[tmp_int] = var;
	}
	return (SUCCESS);
}
