#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include "executor.h"
#include "../libft/libft.h"
#include "../builtins/builtins.h"
#include "../env/env.h"

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

int	execute_command(t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;
	int		pipes[2];

	if (cmd->cmd.heredoc != NULL)
	{
		if (pipe(pipes) == -1)
			return (ERROR);
	}

	if (execute_builtin(cmd, minishell, &exit_status)) // TODO ce exit status n'a pas a etre WEXITSTATUS !!!
		return (exit_status);
	exit_status = 0;
	if (fork1() == 0)
	{
        // LATER faire attention a ce que execute pipeline aie la meme chose !!
		replace_argv0_with_full_path(cmd, minishell);

		if (cmd->cmd.heredoc != NULL)
		{
			// redirect stdin to the pipe
			dup2(pipes[0], STDIN_FILENO);
			close(pipes[0]);
			close(pipes[1]);
		}

		execve(cmd->cmd.argv[0], cmd->cmd.argv, minishell->env_copy);
		perror("execv");
		exit(EXIT_FAILURE); // TODO
	}
	if (cmd->cmd.heredoc != NULL)
	{
		write(pipes[1], cmd->cmd.heredoc, ft_strlen(cmd->cmd.heredoc));
		close(pipes[0]);
		close(pipes[1]);
	}
	wait(&exit_status);
	return (exit_status);
}

int execute_redir(t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;
	int		to_reopen;
	int		std_x_fileno;

	exit_status = 0;
	if (cmd->type == REDIR_IN)
		std_x_fileno = STDIN_FILENO;
	else
		std_x_fileno = STDOUT_FILENO;

	if (cmd->type == REDIR_APPEND)
		cmd->redir.fd = open(cmd->redir.filename, O_APPEND | O_CREAT | O_RDWR, 0000644);
	else if (cmd->type == REDIR_OUT)
		cmd->redir.fd = open(cmd->redir.filename, O_TRUNC | O_CREAT | O_RDWR, 0000644);
	else if (cmd->type == REDIR_IN)
		cmd->redir.fd = open(cmd->redir.filename, O_RDONLY);
	if (cmd->redir.fd == -1)
	{
		perror("open"); // TODO nom d'erreur complet
		exit(EXIT_FAILURE);
	}

	to_reopen = dup(std_x_fileno);
	close(std_x_fileno);
	dup(cmd->redir.fd);

	exit_status = execute(cmd->redir.cmd, minishell);

	close(cmd->redir.fd);
	dup2(to_reopen, std_x_fileno);
	return (exit_status);
}

int	execute_logic(t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;
	int		left_exit_status;

	exit_status = 0;
	left_exit_status = execute(cmd->logic.left, minishell);
	if (cmd->type == LOGIC_AND && left_exit_status == 0)
		exit_status = execute(cmd->logic.right, minishell);
	else if (cmd->type == LOGIC_AND && left_exit_status != 0)
		exit_status = left_exit_status;
	else if (cmd->type == LOGIC_OR && left_exit_status != 0)
		exit_status = execute(cmd->logic.right, minishell);
	else if (cmd->type == LOGIC_OR && left_exit_status == 0)
		exit_status = left_exit_status;
	else 
		return (exit_status);
	return (exit_status);
}


// return un status qui dois etre "extrait" a l'aide de WEXITSTATUS(exit_status) 
// pour recuperer le bon code de sortie
int	execute(t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;

	exit_status = 0;
	if (cmd->type == COMMAND)
		exit_status = execute_command(cmd, minishell);
	else if (cmd->type == REDIR_IN || cmd->type == REDIR_OUT || cmd->type == REDIR_APPEND)
		exit_status = execute_redir(cmd, minishell);
	else if (cmd->type == PIPELINE)
		exit_status = execute_pipeline(cmd, minishell);
	else if (cmd->type == LOGIC_AND || cmd->type == LOGIC_OR)
		exit_status = execute_logic(cmd, minishell);
	else
	{
		// TODO cannot happen ?
		printf("execute: unknown command type: %d\n", cmd->type);
	}
	minishell->last_exit_status = exit_status; // TODO WEXITSTATUS ??
	return (exit_status);
}
