/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:20:35 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 14:31:26 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "executor.h"

void	wait_all(t_cmd *pipeline_cmd, int *exit_status)
{
	int		i;

	i = 0;
	while (i < pipeline_cmd->s_pipeline.pipe_count)
	{
		waitpid(pipeline_cmd->s_pipeline.pids[i], exit_status, 0);
		i++;
	}
}

// malloc OK !
static int	init_(t_cmd *cmd, int *shitty_pipe, t_minishell *minishell)
{
	if (pipe(shitty_pipe) == -1)
	{
		printf("error avec le pipe, 1ere commande : %s\n",
			cmd->s_pipeline.first_cmd->s_command.argv[0]);
		return (ERROR);
	}
	cmd->s_pipeline.pipes
		= (int *)malloc(sizeof(int) * cmd->s_pipeline.pipe_count * 2);
	if (cmd->s_pipeline.pipes == NULL)
		malloc_error(minishell);
	return (SUCCESS);
}

// malloc OK !
int	init_pipes(t_cmd *cmd, int *shitty_pipe, t_minishell *minishell)
{
	int		i;

	if (init_(cmd, shitty_pipe, minishell) == ERROR)
		return (ERROR);
	i = 0;
	while (i < cmd->s_pipeline.pipe_count)
	{
		if (pipe(cmd->s_pipeline.pipes + (i * 2)) == -1)
		{
			perror("pipe");
			return (ERROR);
		}
		i++;
	}
	cmd->s_pipeline.pids
		= (int *)malloc(sizeof(int) * cmd->s_pipeline.pipe_count);
	if (cmd->s_pipeline.pids == NULL)
		malloc_error(minishell);
	return (SUCCESS);
}

t_bool	is_last_cmd(t_cmd *pipeline_cmd, int index)
{
	return ((t_bool)(index == pipeline_cmd->s_pipeline.pipe_count - 1));
}

t_bool	has_next_cmd_heredoc(t_cmd *cmd_cursor)
{
	return ((t_bool)(cmd_cursor->s_command.next != NULL
		&& cmd_cursor->s_command.next->s_command.heredoc != NULL));
}
