/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:19 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/15 11:45:13 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include "../env/env.h"
#include <unistd.h>
#include <stdio.h>

static int	remove_env_var(t_minishell *minishell, int index_var)
{
	int		last;

	last = 0;
	while (minishell->env_copy[last] != NULL)
		last++;
	free(minishell->env_copy[index_var]);
	minishell->env_copy[index_var] = minishell->env_copy[last - 1];
	minishell->env_copy[last - 1] = NULL;
	return (SUCCESS);
}

static int	unset_one_variable(t_minishell *minishell, char *arg)
{
	int		var_index;
	int		i;

	if (ft_isdigit(arg[0]) != 0)
		return (SUCCESS);
	i = 0;
	while (arg[i]
		&& (ft_isdigit(arg[i]) || ft_isalpha(arg[i]) || arg[i] == '_'))
		i++;
	if (arg[i] != '\0')
		return (SUCCESS);
	arg[i] = '\0';
	var_index = get_env_var_index((const char **)minishell->env_copy, arg);
	if (var_index == -1)
		return (SUCCESS);
	remove_env_var(minishell, var_index);
	return (SUCCESS);
}

int	unset(t_minishell *minishell, char **args)
{
	int	last_status;
	int	i;

	if (args[1] == NULL)
		return (SUCCESS);
	i = 0;
	while (++i && args[i])
		last_status = unset_one_variable(minishell, args[i]);
	return (last_status);
}
