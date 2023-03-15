/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:04 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/15 11:36:53 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "../libft/libft.h"
#include "../minishell.h"
#include "../env/env.h"

int	check_invalid_identifier(char *argu)
{
	int	i;

	i = 0;
	if (ft_strchr(argu, '=') == 0)
		return (3);
	if (ft_strchr(argu, '=') != ft_strrchr(argu, '=') || ft_isdigit(argu[0]))
	{
		ft_putendl_fd(STR"minishell: export: not a valid identifier", 2);
		return (ERROR);
	}
	while (argu[i] && argu[i] != '='
		&& (ft_isdigit(argu[i]) || ft_isalpha(argu[i]) || argu[i] == '_'))
		i++;
	if ((ft_isdigit(argu[i]) == 0 || ft_isalpha(argu[i]) == 0)
		&& argu[i] != '=')
	{
		ft_putendl_fd(STR"minishell: export: not a valid identifier", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	check_var_name(char *var)
{
	int	len;
	int	status;

	len = ft_strlen(var);
	if (len == 1)
	{
		if (ft_isalpha(var[0]))
			return (3);
		ft_putendl_fd(STR"minishell: export: not a valid identifier", 2);
		return (ERROR);
	}
	else
	{
		status = check_invalid_identifier(var);
		if (status != SUCCESS)
			return (status);
		if (var[0] == '_' && var[1] == '=')
			return (3);
	}
	return (SUCCESS);
}

int	export_one_arg(t_minishell *minishell, char *var)
{
	char	*new_var;
	int		status;
	int		var_index;

	status = check_var_name(var);
	if (status == ERROR)
		return (ERROR);
	if (status == 3)
		return (SUCCESS);
	new_var = ft_strdup(var);
	if (new_var == NULL)
		return (ERROR);
	var_index = get_env_var_index((const char **)minishell->env_copy, new_var);
	if (var_index == -1 && add_env_var(minishell, new_var) == ERROR)
	{
		free(new_var);
		return (ERROR);
	}
	else if (var_index != -1)
	{
		free(minishell->env_copy[var_index]);
		minishell->env_copy[var_index] = new_var;
	}
	return (SUCCESS);
}

int	export_(t_minishell *minishell, char **argv)
{
	int	last_status;
	int	i;

	i = 1;
	if (argv[1] == NULL)
		return (print_all_env(minishell));
	else
	{
		while (argv[i] != NULL)
		{
			last_status = export_one_arg(minishell, argv[i]);
			i++;
		}
	}
	return (last_status);
}
