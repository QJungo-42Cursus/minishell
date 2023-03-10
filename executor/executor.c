/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:20:43 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/09 15:04:54 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include "executor.h"
#include "../libft/libft.h"
#include "../builtins/builtins.h"
#include "../env/env.h"

int	execute(t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;

	exit_status = 0;
	if (cmd->type == COMMAND)
		exit_status = execute_command(cmd, minishell);
	else if (cmd->type == REDIR_IN
		|| cmd->type == REDIR_OUT || cmd->type == REDIR_APPEND)
		exit_status = execute_redir(cmd, minishell);
	else if (cmd->type == PIPELINE)
		exit_status = execute_pipeline(cmd, minishell);
	minishell->last_exit_status = exit_status;
	return (exit_status);
}
