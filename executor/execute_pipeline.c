/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:20:33 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/06 14:09:48 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "executor.h"

typedef struct s_norm {
	int		i;
	t_cmd	*pipeline_cmd;
	t_cmd	*cmd_cursor;
	int		shitty_pipe[2];
	int		heredoc_pipe[2];
}	t_norm;

static void	set_pipes(t_norm n)
{
	if (n.i == 0 && n.cmd_cursor->s_command.heredoc)
	{
		dup2(n.heredoc_pipe[STDIN_FILENO], STDIN_FILENO);
		close(n.heredoc_pipe[STDIN_FILENO]);
		close(n.heredoc_pipe[STDOUT_FILENO]);
	}
	if (n.i != 0)
		dup2(n.pipeline_cmd->s_pipeline.pipes[pipe_index(n.i - 1,
				STDIN_FILENO)], STDIN_FILENO);
	if (has_next_cmd_heredoc(n.cmd_cursor))
	{
		dup2(n.shitty_pipe[STDOUT_FILENO], STDOUT_FILENO);
		close(n.shitty_pipe[STDIN_FILENO]);
		close(n.shitty_pipe[STDOUT_FILENO]);
	}
	else if (!is_last_cmd(n.pipeline_cmd, n.i))
		dup2(n.pipeline_cmd->s_pipeline.pipes[pipe_index(n.i, STDOUT_FILENO)],
			STDOUT_FILENO);
	close_all_pipes(n.pipeline_cmd->s_pipeline.pipes,
		n.pipeline_cmd->s_pipeline.pipe_count);
}

static void	run_exec(t_minishell *minishell,
		t_cmd *cmd_cursor, int *exit_status)
{
	if (execute_builtin(cmd_cursor, minishell, exit_status))
		exit(*exit_status);
	replace_argv0_with_full_path(cmd_cursor, minishell);
	execve(cmd_cursor->s_command.argv[0],
		cmd_cursor->s_command.argv, minishell->env_copy);
	perror("execvp");
	exit(EXIT_FAILURE);
}

static void	m(t_norm n,
		t_minishell *minishell, int *exit_status)
{
	pipe(n.heredoc_pipe);
	n.cmd_cursor = n.pipeline_cmd->s_pipeline.first_cmd;
	n.i = 0;
	while (n.i < n.pipeline_cmd->s_pipeline.pipe_count)
	{
		n.pipeline_cmd->s_pipeline.pids[n.i] = fork();
		if (n.pipeline_cmd->s_pipeline.pids[n.i] == 0)
		{
			set_pipes(n);
			run_exec(minishell, n.cmd_cursor, exit_status);
		}
		if (n.cmd_cursor->s_command.heredoc != NULL && n.i != 0)
			ft_putstr_fd(n.cmd_cursor->s_command.heredoc, n.pipeline_cmd
				->s_pipeline.pipes[pipe_index(n.i - 1, STDOUT_FILENO)]);
		if (n.cmd_cursor->s_command.heredoc != NULL && n.i == 0)
		{
			ft_putstr_fd(n.cmd_cursor->s_command.heredoc,
				n.heredoc_pipe[STDOUT_FILENO]);
			close(n.heredoc_pipe[STDIN_FILENO]);
			close(n.heredoc_pipe[STDOUT_FILENO]);
		}
		n.cmd_cursor = n.cmd_cursor->s_command.next;
		n.i++;
	}
}

extern volatile sig_atomic_t	g_minishell_status;

int	execute_pipeline(t_cmd *pipeline_cmd, t_minishell *minishell)
{
	int		exit_status;
	t_norm	n;

	n.pipeline_cmd = pipeline_cmd;
	if (init_pipes(pipeline_cmd, n.shitty_pipe, minishell) == ERROR)
		malloc_error(minishell);
	exit_status = 0;
	g_minishell_status = S_EXEC;
	m(n, minishell, &exit_status);
	close_all_pipes(pipeline_cmd->s_pipeline.pipes,
		pipeline_cmd->s_pipeline.pipe_count);
	wait_all(pipeline_cmd, &exit_status);
	g_minishell_status = S_PROMPT;
	return (WEXITSTATUS(exit_status));
}
