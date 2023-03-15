/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:20:41 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 14:21:48 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "executor.h"
#include "../libft/libft.h"
#include "../builtins/builtins.h"
#include "../env/env.h"

int	execute_redir(t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;
	int		to_reopen;
	int		std_x_fileno;

	if (cmd->s_redir.fd == -1)
		return (1);// sure ?
	if (cmd->type == REDIR_IN)
		std_x_fileno = STDIN_FILENO;
	else
		std_x_fileno = STDOUT_FILENO;
	exit_status = 0;
	to_reopen = dup(std_x_fileno);
	close(std_x_fileno);
	dup(cmd->s_redir.fd);
	if (cmd->s_redir.cmd == NULL)
		exit_status = 0;
	else
		exit_status = execute(cmd->s_redir.cmd, minishell);
	close(cmd->s_redir.fd);
	dup2(to_reopen, std_x_fileno);
	return (exit_status);
}
