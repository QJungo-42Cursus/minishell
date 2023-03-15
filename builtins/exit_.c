/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:00 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/15 11:09:36 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>

void	free_minishell(t_minishell *minishell)
{
	free(minishell->prompt_msg);
	split_free(minishell->env_copy);
	rl_clear_history();
}

static int	ft_ascii_is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	exit_(t_minishell *minishell, char **argv, int exit_status)
{
	int			len;
	long int	num;

	len = 0;
	while (argv != NULL && argv[len] != NULL)
		len++;
	if (len >= 2)
	{
		if (ft_ascii_is_valid_number(argv[1]) == 0)
		{
			ft_putendl_fd(STR"minishell: exit: numeric argument required", 2);
			exit_status = 255;
		}
		if (len > 2)
		{
			ft_putendl_fd(STR"minishell: exit: too many arguments", 2);
			return (ERROR);
		}
		num = long_atoi(argv[1]);
		exit_status = num;
	}
	free_minishell(minishell);
	printf("exit\n");
	exit(exit_status);
	return (SUCCESS);
}
