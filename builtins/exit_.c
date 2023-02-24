/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:00 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 13:39:19 by qjungo           ###   ########.fr       */
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

int	exit_(t_minishell *minishell, char **argv, int exit_status)
{
	if (argv[1] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (ERROR);
	}
	free_minishell(minishell);
	exit(exit_status);
	return (SUCCESS);
}
