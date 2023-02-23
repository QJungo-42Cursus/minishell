#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "executor.h"
#include "../tests/debug_helper.h"

static void	set_pipes(int i,
		t_cmd *pipeline_cmd, t_cmd *cmd_cursor, int *shitty_pipe)
{
	if (i != 0)
		dup2(pipeline_cmd->pipeline.pipes[pipe_index(i - 1, STDIN_FILENO)],
			STDIN_FILENO);
	if (has_next_cmd_heredoc(cmd_cursor))
	{
		dup2(shitty_pipe[STDOUT_FILENO], STDOUT_FILENO);
		close(shitty_pipe[STDIN_FILENO]);
		close(shitty_pipe[STDOUT_FILENO]);
	}
	else if (!is_last_cmd(pipeline_cmd, i))
		dup2(pipeline_cmd->pipeline.pipes[pipe_index(i, STDOUT_FILENO)],
			STDOUT_FILENO);
	close_all_pipes(pipeline_cmd->pipeline.pipes,
		pipeline_cmd->pipeline.pipe_count);
}

static void	run_exec(t_minishell *minishell,
		t_cmd *cmd_cursor, int *exit_status)
{
	if (execute_builtin(cmd_cursor, minishell, exit_status))
		exit(*exit_status);
	replace_argv0_with_full_path(cmd_cursor, minishell);
	execve(cmd_cursor->cmd.argv[0], cmd_cursor->cmd.argv, minishell->env_copy);
	perror("execvp");
	exit(EXIT_FAILURE);
}

static void	m(t_cmd *pipeline_cmd,
		t_minishell *minishell, int *shitty_pipe, int *exit_status)
{
	int		i;
	t_cmd	*cmd_cursor;

	cmd_cursor = pipeline_cmd->pipeline.first_cmd;
	i = 0;
	while (i < pipeline_cmd->pipeline.pipe_count)
	{
		pipeline_cmd->pipeline.pids[i] = fork();
		if (pipeline_cmd->pipeline.pids[i] == 0)
		{
			set_pipes(i, pipeline_cmd, cmd_cursor, shitty_pipe);
			run_exec(minishell, cmd_cursor, exit_status);
		}
		if (cmd_cursor->cmd.heredoc != NULL)
			write(pipeline_cmd->pipeline.pipes[pipe_index(i - 1,
					STDOUT_FILENO)], cmd_cursor->cmd.heredoc,
				ft_strlen(cmd_cursor->cmd.heredoc));
		cmd_cursor = cmd_cursor->cmd.next;
		i++;
	}
}

int	execute_pipeline(t_cmd *pipeline_cmd, t_minishell *minishell)
{
	int		exit_status;
	int		shitty_pipe[2];

	if (init_pipes(pipeline_cmd, shitty_pipe) == ERROR)
		// TODO
		return (ERROR);
	exit_status = 0;
	m(pipeline_cmd, minishell, shitty_pipe, &exit_status);
	close_all_pipes(pipeline_cmd->pipeline.pipes,
		pipeline_cmd->pipeline.pipe_count);
	wait_all(pipeline_cmd, &exit_status);
	return (WEXITSTATUS(exit_status));
}
