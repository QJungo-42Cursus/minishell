/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:00:55 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/14 14:29:22 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>

static int	check_args(char **argv)
{
	if (argv[1] != NULL)
	{
		write(2, "minishell: env: too many arguments\n", 34);
		return (ERROR);
	}
	return (SUCCESS);
}

int	env(t_minishell *minishell, char **argv)
{
	int		i;

	if (check_args(argv) == ERROR)
		return (ERROR);
	i = 0;
	while (minishell->env_copy[i] != NULL)
	{
		printf("%s\n", minishell->env_copy[i]);
		i++;
	}
	return (SUCCESS);
}

int	print_all_env(t_minishell *minishell)
{
	int		i;

	i = 0;
	while (minishell->env_copy[i] != NULL)
	{
		printf(STR"declare -x %s\n", minishell->env_copy[i]);
		i++;
	}
	return (SUCCESS);
}
