#include "executor.h"
#include "../builtins/builtins.h"

int	execute_builtin(t_cmd *cmd, t_minishell *minishell, int *exit_status)
{
	char	*cmd_name;

	cmd_name = cmd->cmd.argv[0];
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		*exit_status = echo(cmd->cmd.argv);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		*exit_status = cd(minishell, cmd->cmd.argv);
	else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		*exit_status = pwd(minishell, cmd->cmd.argv);
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		*exit_status = export_(minishell, cmd->cmd.argv);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		*exit_status = unset(minishell, cmd->cmd.argv);
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		*exit_status = env(minishell, cmd->cmd.argv);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		*exit_status = exit_(minishell, cmd->cmd.argv, SUCCESS);
	else
		return (FALSE);
	return (TRUE);
}
