/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:53 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/11 11:02:19 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_command(t_cmd *cmd)
{
	if (cmd->s_command.argv != NULL)
		split_free(cmd->s_command.argv);
	cmd->s_command.argv = NULL;
	if (cmd->s_command.heredoc != NULL)
		free(cmd->s_command.heredoc);
	cmd->s_command.heredoc = NULL;
	if (cmd->s_command.next != NULL)
		free_ast(cmd->s_command.next);
}

static void	free_pipeline(t_cmd *cmd)
{
	if (cmd->s_pipeline.first_cmd != NULL)
		free_ast(cmd->s_pipeline.first_cmd);
	cmd->s_pipeline.first_cmd = NULL;
	if (cmd->s_pipeline.pipes != NULL)
		free(cmd->s_pipeline.pipes);
	cmd->s_pipeline.pipes = NULL;
	if (cmd->s_pipeline.pids != NULL)
		free(cmd->s_pipeline.pids);
	cmd->s_pipeline.pids = NULL;
}

void	free_ast(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->type == COMMAND)
		free_command(cmd);
	else if (cmd->type == PIPELINE)
		free_pipeline(cmd);
	else if (cmd->type == REDIR_OUT
		|| cmd->type == REDIR_IN || cmd->type == REDIR_APPEND)
		free_ast(cmd->s_redir.cmd);
	free(cmd);
}
