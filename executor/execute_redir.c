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

static int	check_error(t_cmd *cmd)
{
	if ((cmd->type == REDIR_APPEND || cmd->type == REDIR_OUT)
		&& access(cmd->s_redir.filename, F_OK) != 0)
		return (SUCCESS);
	if ((cmd->type == REDIR_APPEND || cmd->type == REDIR_OUT)
		&& access(cmd->s_redir.filename, W_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, cmd->s_redir.filename, ft_strlen(cmd->s_redir.filename));
		write(2, ": Permission denied\n", 20);
		return (ERROR);
	}
	if (cmd->type == REDIR_IN && access(cmd->s_redir.filename, R_OK) != 0)
	{
		write(2, "minishell: ", 11);
		write(2, cmd->s_redir.filename, ft_strlen(cmd->s_redir.filename));
		write(2, ": Permission denied\n", 20);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	open_file(t_cmd *cmd)
{
	if (cmd->type == REDIR_APPEND)
		cmd->s_redir.fd = open(cmd->s_redir.filename,
				O_APPEND | O_CREAT | O_RDWR, 0000644);
	else if (cmd->type == REDIR_OUT)
		cmd->s_redir.fd = open(cmd->s_redir.filename,
				O_TRUNC | O_CREAT | O_RDWR, 0000644);
	else if (cmd->type == REDIR_IN)
		cmd->s_redir.fd = open(cmd->s_redir.filename, O_RDONLY);
	if (cmd->s_redir.fd == -1)
	{
		// TODO nom d'erreur complet
		perror("open");
		exit(EXIT_FAILURE);
		return (ERROR);
	}
	return (SUCCESS);
}

int	execute_redir(t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;
	int		to_reopen;
	int		std_x_fileno;

	if (check_error(cmd) == ERROR)
		return (ERROR);
	if (cmd->type == REDIR_IN)
		std_x_fileno = STDIN_FILENO;
	else
		std_x_fileno = STDOUT_FILENO;
	exit_status = 0;
	if (open_file(cmd) == ERROR)
		return (ERROR);
	to_reopen = dup(std_x_fileno);
	close(std_x_fileno);
	dup(cmd->s_redir.fd);
	exit_status = execute(cmd->s_redir.cmd, minishell);
	close(cmd->s_redir.fd);
	dup2(to_reopen, std_x_fileno);
	return (exit_status);
}
