/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:20:46 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:20:47 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../parser/parser.h"
#include "../minishell.h"
#include "../env/env.h"

int	fork1(void)
{
	int		pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	close_all_pipes(int *fds, int pipe_count)
{
	int		i;

	i = 0;
	while (i < pipe_count * 2)
	{
		close(fds[i]);
		i++;
	}
}

int	pipe_index(int i, int read)
{
	return (i * 2 + read);
}

void	replace_argv0_with_full_path(t_cmd *cmd, t_minishell *minishell)
{
	char	*path;
	char	**env_paths;

	env_paths = get_paths_in_env(minishell->env_copy);
	// TODO error handling
	if (env_paths == NULL)
		return ;
	path = find_cmd_path(cmd->s_command.argv[0], env_paths);
	// TODO error handling
	if (path == NULL)
		return ;
	split_free(env_paths);
	free(cmd->s_command.argv[0]);
	cmd->s_command.argv[0] = path;
}
