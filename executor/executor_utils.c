#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../parser/parser.h"
#include "../minishell.h"
#include "../env/env.h"

int	fork1()
{
	int pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	close_all_pipes(int *fds, int pipe_count)
{
	int i = 0;
	while (i < pipe_count * 2)
	{
		close(fds[i]);
		i++;
	}
}

int pipe_index(int i, int read)
{
	return (i * 2 + read);
}

void	replace_argv0_with_full_path(t_cmd *cmd, t_minishell *minishell)
{
	char	*path;
	char	**env_paths;

	env_paths = get_paths_in_env(minishell->env_copy);
	if (env_paths == NULL)
		return ; // TODO error handling
	path = find_cmd_path(cmd->cmd.argv[0], env_paths);
	if (path == NULL)
		return ; // TODO error handling
	split_free(env_paths);
	free(cmd->cmd.argv[0]);
	cmd->cmd.argv[0] = path;
}
