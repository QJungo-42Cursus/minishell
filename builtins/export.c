/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:04 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:16:36 by qjungo           ###   ########.fr       */
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

// malloc OK !
static int	add_env_var(t_minishell *mini, char *var)
{
	char	**new_env_copy;
	int		i;

	new_env_copy
		= (char **)malloc(sizeof(char *) * list_len(mini->env_copy) + 1);
	if (new_env_copy == NULL)
		return (ERROR);
	i = 0;
	while (mini->env_copy[i] != NULL)
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

static int	check_var_name(char *var)
{
	if (ft_strchr(var, '=') == NULL)
	{
		// TODO Message error // no error ?
		write(2, "minishell: export: not a valid identifier\n", 42);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	print_all(t_minishell *minishell)
{
	int		i;

	i = 0;
	while (minishell->env_copy[i] != NULL)
	{
		printf("declare -x %s\n", minishell->env_copy[i]);
		i++;
	}
	return (SUCCESS);
}

int	export_(t_minishell *minishell, char **argv)
{
	char	*var;
	int		var_index;

	if (argv[1] == NULL)
		return (print_all(minishell));
	if (check_var_name(argv[1]) == ERROR)
		return (ERROR);
	var = ft_strdup(argv[1]);
	if (var == NULL)
		return (ERROR);
	var_index = get_env_var_index((const char **)minishell->env_copy, var);
	if (var_index == -1)
	{
		if (add_env_var(minishell, var) == ERROR)
		{
			free(var);
			return (ERROR);
		}
	}
	else
	{
		free(minishell->env_copy[var_index]);
		minishell->env_copy[var_index] = var;
	}
	return (SUCCESS);
}
