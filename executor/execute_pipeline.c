#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include "executor.h"

#include "../tests/debug_helper.h"

int	init_pipes(t_cmd *cmd)
{
	int		i;

	i = 0;
	cmd->pipeline.pipes = (int *)malloc(sizeof(int) * cmd->pipeline.pipe_count * 2);
	if (cmd->pipeline.pipes == NULL)
	{
		printf("malloc error\n");
		return (ERROR);
	}
	while (i < cmd->pipeline.pipe_count)
	{
		if (pipe(cmd->pipeline.pipes + (i * 2)) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
			return (ERROR);
		}
		i++;
	}
	cmd->pipeline.pids = (int *)malloc(sizeof(int) * cmd->pipeline.pipe_count);
	return (SUCCESS);
}

int execute_pipeline(t_cmd *pipeline_cmd)
{
	int		exit_status;
	int		i;
	t_cmd	*cmd_cursor;

	if (pipeline_cmd == NULL)
	{
		printf("execute_pipeline: cmd is NULL\n");
		exit(EXIT_FAILURE);
	}

	if (init_pipes(pipeline_cmd) == ERROR)
		// TODO
		return (ERROR);

	exit_status = 0;
	i = 0;
	cmd_cursor = pipeline_cmd->pipeline.first_cmd;

	if (cmd_cursor == NULL)
	{
		printf("execute_pipeline: cmd_cursor is NULL\n");
		exit(EXIT_FAILURE);
	}


	while (i < pipeline_cmd->pipeline.pipe_count + 1)
	{
		pipeline_cmd->pipeline.pids[i] = fork();
		if (pipeline_cmd->pipeline.pids[i] == 0)
		{
			if (i != 0) /* si c'est pas la premiere command */
				dup2(pipeline_cmd->pipeline.pipes[pipe_index(i - 1, STDIN_FILENO)], STDIN_FILENO);
			if (i != pipeline_cmd->pipeline.pipe_count) /* si c'est pas la fin */
				dup2(pipeline_cmd->pipeline.pipes[pipe_index(i, STDOUT_FILENO)], STDOUT_FILENO);
			// TODO si ici je met une fonction custom qui s'occupe des here_doc, c'est niquel
			// en fait les here_doc sont gerer avant l'exécution
			// Ca doit etre intersepter par le parser et gerer (input) avant l'execution
			//
			// On peut l'enregistrer dans une variable et le write dans le pipe en question
			// Si on a une struct cmd, on peu mettre la variable dedans, si c'est non null, on redirige
			//
			// -
			// C'est aussi ici qu'on va print les erreurs command not found
			// le pipe va continuer a tourner meme si la commande n'existe pas
			close_all_pipes(pipeline_cmd->pipeline.pipes, pipeline_cmd->pipeline.pipe_count);
			execvp(cmd_cursor->cmd.argv[0], cmd_cursor->cmd.argv);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		cmd_cursor = cmd_cursor->cmd.next;
		i++;
	}
	close_all_pipes(pipeline_cmd->pipeline.pipes, pipeline_cmd->pipeline.pipe_count);
	/* wait */
	i = 0;
	while (i < pipeline_cmd->pipeline.pipe_count)
	{
		waitpid(pipeline_cmd->pipeline.pids[i], &exit_status, 0);
		i++;
	}
	return (exit_status);
}
