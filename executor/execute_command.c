/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:20:30 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/06 14:39:13 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "executor.h"

extern volatile sig_atomic_t	g_minishell_status;

// LATER refactoriser pour que pipeline ai la meme chose !
void	child(t_minishell *minishell, t_cmd *cmd, int pipes[2])
{
	replace_argv0_with_full_path(cmd, minishell);
	if (cmd->s_command.heredoc != NULL)
	{
		dup2(pipes[0], STDIN_FILENO);
		close(pipes[0]);
		close(pipes[1]);
	}
	if (access(cmd->s_command.argv[0], F_OK) == -1)
	{
		ft_putstr_fd((char *)"minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->s_command.argv[0], STDERR_FILENO);
		ft_putstr_fd((char *)": command not found\n", STDERR_FILENO);
		exit(127);
	}
	execve(cmd->s_command.argv[0], cmd->s_command.argv, minishell->env_copy);
	perror("minishell: execution");
	exit(errno);
}

int	execute_command(t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;
	int		pipes[2];

	if (cmd->s_command.heredoc != NULL)
	{
		if (pipe(pipes) == -1)
			return (ERROR);
	}
	if (execute_builtin(cmd, minishell, &exit_status))
		return (exit_status);
	exit_status = 0;
	g_minishell_status = S_EXEC;
	if (fork1() == 0)
		child(minishell, cmd, pipes);
	if (cmd->s_command.heredoc != NULL)
	{
		write(pipes[1], cmd->s_command.heredoc,
			ft_strlen(cmd->s_command.heredoc));
		close(pipes[0]);
		close(pipes[1]);
	}
	wait(&exit_status);
	g_minishell_status = S_PROMPT;
	return (WEXITSTATUS(exit_status));
}
