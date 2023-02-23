#include "parser.h"

void	free_ast(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->type == COMMAND)
	{
		split_free(cmd->s_command.argv);
		free(cmd->s_command.heredoc);
	}
	else if (cmd->type == PIPELINE)
	{
		free(cmd->s_pipeline.pipes);
		free(cmd->s_pipeline.pids);
		free_ast(cmd->s_pipeline.first_cmd);
	}
	else if (cmd->type == REDIR_OUT
		|| cmd->type == REDIR_IN || cmd->type == REDIR_APPEND)
	{
		free(cmd->s_redir.filename);
		free_ast(cmd->s_redir.cmd);
	}
	else if (cmd->type == LOGIC_AND || cmd->type == LOGIC_OR)
	{
		free_ast(cmd->s_logic.left);
		free_ast(cmd->s_logic.right);
	}
	free(cmd);
}
