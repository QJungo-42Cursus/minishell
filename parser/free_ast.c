#include "parser.h"

/*
   struct {
   struct s_cmd *left;
   struct s_cmd *right;
   } pipe;
*/

void	free_ast(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->type == COMMAND)
	{
		split_free(cmd->cmd.argv);
		free(cmd->cmd.heredoc);
	}
	else if (cmd->type == PIPELINE)
	{
		free(cmd->pipeline.pipes);
		free(cmd->pipeline.pids);
		free_ast(cmd->pipeline.first_cmd);
	}
	else if (cmd->type == REDIR_OUT || cmd->type == REDIR_IN || cmd->type == REDIR_APPEND)
	{
		free(cmd->redir.filename);
		free_ast(cmd->redir.cmd);
	}
	else if (cmd->type == LOGIC_AND || cmd->type == LOGIC_OR)
	{
		free_ast(cmd->logic.left);
		free_ast(cmd->logic.right);
	}
	free(cmd);
}

