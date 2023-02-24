/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:53 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:01:54 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_command(t_cmd *cmd)
{
	split_free(cmd->s_command.argv);
	cmd->s_command.argv = NULL;
	free(cmd->s_command.heredoc);
	cmd->s_command.heredoc = NULL;
	if (cmd->s_command.next != NULL)
		free_ast(cmd->s_command.next);
}

void	free_ast(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->type == COMMAND)
		free_command(cmd);
	else if (cmd->type == PIPELINE)
	{
		free(cmd->s_pipeline.pipes);
		cmd->s_pipeline.pipes = NULL;
		free(cmd->s_pipeline.pids);
		cmd->s_pipeline.pids = NULL;
		free_ast(cmd->s_pipeline.first_cmd);
	}
	else if (cmd->type == REDIR_OUT
		|| cmd->type == REDIR_IN || cmd->type == REDIR_APPEND)
	{
		free(cmd->s_redir.filename);
		cmd->s_redir.filename = NULL;
		free_ast(cmd->s_redir.cmd);
	}
	else if (cmd->type == LOGIC_AND || cmd->type == LOGIC_OR)
	{
		free_ast(cmd->s_logic.left);
		free_ast(cmd->s_logic.right);
	}
	free(cmd);
}
