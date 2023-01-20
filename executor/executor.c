#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include "executor.h"

int	execute_command(t_cmd *cmd)
{
	int		exit_status;

	exit_status = 0;
	if (fork1() == 0)
	{
		execvp(cmd->cmd.argv[0], cmd->cmd.argv);
		perror("execvp");
		exit(EXIT_FAILURE); // TODO
	}
	wait(&exit_status);
	return (exit_status);
}

int execute_redir(t_cmd *cmd)
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

	exit_status = execute(cmd->redir.cmd);

	close(cmd->redir.fd);
	dup2(to_reopen, std_x_fileno);

	return (exit_status);
}

int execute_pipeline(t_cmd *cmd)
{
	int		exit_status;
	int		i;

	exit_status = 0;
	/* init pipes */
	i = 0;
	cmd->pipeline.pipes = (int *)malloc(sizeof(int) * cmd->pipeline.pipe_count * 2);
	while (i < cmd->pipeline.pipe_count)
	{
		if (pipe(cmd->pipeline.pipes + (i * 2)) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	/* run */
	i = 0;
	t_cmd *cmd_it = cmd->pipeline.first_cmd;
	while (i < cmd->pipeline.pipe_count)
	{
		cmd->pipeline.pids[i] = fork();
		if (cmd->pipeline.pids[i] == 0)
		{
			if (i != 0) /* si c'est pas la premiere command */
				dup2(cmd->pipeline.pipes[pipe_index(i - 1, STDIN_FILENO)], STDIN_FILENO);
			if (i != cmd->pipeline.pipe_count - 1) /* si c'est pas la fin */
				dup2(cmd->pipeline.pipes[pipe_index(i, STDOUT_FILENO)], STDOUT_FILENO);
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
			close_all_pipes(cmd->pipeline.pipes, cmd->pipeline.pipe_count);
			execvp(cmd_it->cmd.argv[0], cmd_it->cmd.argv);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		cmd_it = cmd_it->cmd.next;
		i++;
	}
	close_all_pipes(cmd->pipeline.pipes, cmd->pipeline.pipe_count);
	/* wait */
	i = 0;
	while (i < cmd->pipeline.pipe_count)
	{
		if (i == cmd->pipeline.pipe_count - 1)
			waitpid(cmd->pipeline.pids[i], &exit_status, 0);
		else
			waitpid(cmd->pipeline.pids[i], NULL, 0);
		i++;
	}
	return (exit_status);
}

int execute_logic(t_cmd *cmd)
{
	int		exit_status;
	int		left_exit_status;

	left_exit_status = execute(cmd->logic.left);
	if (cmd->type == LOGIC_AND && left_exit_status == 0)
		exit_status = execute(cmd->logic.right);
	else if (cmd->type == LOGIC_AND && left_exit_status != 0)
		exit_status = left_exit_status;
	else if (cmd->type == LOGIC_OR && left_exit_status != 0)
		exit_status = execute(cmd->logic.right);
	else if (cmd->type == LOGIC_OR && left_exit_status == 0)
		exit_status = left_exit_status;
	return (exit_status);
}


// return un status qui dois etre "extrait" a l'aide de WEXITSTATUS(exit_status) 
// pour recuperer le bon code de sortie
int	execute(t_cmd *cmd)
{
	int		exit_status;

	exit_status = 0;
	if (cmd->type == COMMAND)
		exit_status = execute_command(cmd);
	else if (cmd->type == REDIR_IN || cmd->type == REDIR_OUT || cmd->type == REDIR_APPEND)
		exit_status = execute_redir(cmd);
	else if (cmd->type == PIPELINE)
		exit_status = execute_pipeline(cmd);
	else if (cmd->type == LOGIC_AND || cmd->type == LOGIC_OR)
		exit_status = execute_logic(cmd);
	else {/* TODO cannot happen ? */}
	return (exit_status);
}

