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

int	execute_logic(t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;
	int		left_exit_status;

	exit_status = 0;
	left_exit_status = execute(cmd->s_logic.left, minishell);
	if (cmd->type == LOGIC_AND && left_exit_status == 0)
		exit_status = execute(cmd->s_logic.right, minishell);
	else if (cmd->type == LOGIC_AND && left_exit_status != 0)
		exit_status = left_exit_status;
	else if (cmd->type == LOGIC_OR && left_exit_status != 0)
		exit_status = execute(cmd->s_logic.right, minishell);
	else if (cmd->type == LOGIC_OR && left_exit_status == 0)
		exit_status = left_exit_status;
	else
		return (exit_status);
	return (exit_status);
}

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
	else if (cmd->type == LOGIC_AND || cmd->type == LOGIC_OR)
		exit_status = execute_logic(cmd, minishell);
	minishell->last_exit_status = exit_status;
	return (exit_status);
}
