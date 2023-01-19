#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

typedef enum e_cmd_type {
	PIPE,			/* cmd | cmd */
	PIPELINE,		/* cmd | cmd | cmd | ... */
	COMMAND,		/* cmd */
	//LOGIC_AND,		/* cmd && cmd */
	//LOGIC_OR,		/* cmd || cmd */
} t_cmd_type;


typedef struct s_cmd {
	t_cmd_type	type;
	union {
		struct {
			struct s_cmd *left;
			struct s_cmd *right;
		} pipe;
		struct {
			char **argv;
			struct s_cmd *next; // only for pipeline
		} cmd;
		struct {
			int	*pipes;
			int	pipe_count; // we could just count the count next commands
			struct s_cmd *first_cmd;
		} pipeline;
		/*
		struct {
			struct s_cmd *left;
			struct s_cmd *right;
		} logic;
		*/
	};
} t_cmd;

int pipe_index(int i, int read);
void	close_all_pipes(int *fds, int pipe_count);

int	fork1();
int	execute(t_cmd *cmd)
{
	int	p[2];
	int exit_status = 0;

	if (cmd->type == PIPE)
	{
		if (pipe(p) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (fork1() == 0)
		{
			close(STDOUT_FILENO);
			dup(p[STDOUT_FILENO]);
			close(p[0]);
			close(p[1]);
			execute(cmd->pipe.left);
		}
		if (fork1() == 0)
		{
			close(STDIN_FILENO);
			dup(p[STDIN_FILENO]);
			close(p[0]);
			close(p[1]);
			execute(cmd->pipe.right);
		}
		close(p[0]);
		close(p[1]);
		//wait(&exit_status);
	}
	else if (cmd->type == PIPELINE)
	{
		/* init pipes */
		int i = 0;
		cmd->pipeline.pipes = malloc(sizeof(int) * cmd->pipeline.pipe_count * 2);
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
			int pid = fork();
			if (pid == 0)
			{
				if (i != 0) /* si c'est la premiere command */
					dup2(cmd->pipeline.pipes[pipe_index(i - 1, STDIN_FILENO)], STDIN_FILENO);
				if (i != cmd->pipeline.pipe_count - 1) /* si c'est la fin */
					dup2(cmd->pipeline.pipes[pipe_index(i, STDOUT_FILENO)], STDOUT_FILENO);
				close_all_pipes(cmd->pipeline.pipes, cmd->pipeline.pipe_count);
				execute(cmd_it);
			}
			cmd_it = cmd_it->cmd.next;
			i++;
		}
		//wait(&exit_status);
	}
	else if (cmd->type == COMMAND)
	{
		if (fork1() == 0)
		{
			execvp(cmd->cmd.argv[0], cmd->cmd.argv);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		wait(&exit_status);
	}
	return (exit_status);
}


t_cmd	*init_example2();
t_cmd	*init_example1();
t_cmd	*init_example0();

int main()
{
	t_cmd	*cmd;
	int		exit_status;

	//cmd = init_example2();
	//exit_status = execute(cmd);
	//wait(NULL);
	//printf("end example 2, exit_status : %d\n\n", exit_status);

	//cmd = init_example1();
	//exit_status = execute(cmd);
	//wait(NULL);
	//printf("end example 1, exit_status : %d\n\n", exit_status);

	cmd = init_example0();
	exit_status = execute(cmd);
	printf("end example 0, exit_status : %d\n\n", exit_status);
}

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

t_cmd	*init_example0()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = COMMAND;
	cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->cmd.argv[0] = strdup("/bin/ls");
	cmd->cmd.argv[1] = strdup("-l");
	cmd->cmd.argv[2] = NULL;
	return (cmd);
}

t_cmd	*init_example1()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = PIPE;
	cmd->pipe.left = malloc(sizeof(t_cmd));
	cmd->pipe.left->type = COMMAND;
	cmd->pipe.left->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipe.left->cmd.argv[0] = strdup("/bin/ls");
	cmd->pipe.left->cmd.argv[1] = strdup("-la");
	cmd->pipe.left->cmd.argv[2] = NULL;
	cmd->pipe.right = malloc(sizeof(t_cmd));
	cmd->pipe.right->type = COMMAND;
	cmd->pipe.right->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipe.right->cmd.argv[0] = strdup("/bin/cat");
	cmd->pipe.right->cmd.argv[1] = strdup("-e");
	cmd->pipe.right->cmd.argv[2] = NULL;
	return (cmd);
}

// example with pipeline
t_cmd	*init_example2()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = PIPELINE;
	cmd->pipeline.pipe_count = 3;
	cmd->pipeline.pipes = malloc(sizeof(int) * 6);

	// first_cmd
	cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/ls");
	cmd->pipeline.first_cmd->cmd.argv[1] = strdup("-la");
	cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	// second_cmd
	cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/cat");
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = strdup("-e");
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next->cmd.next = malloc(sizeof(t_cmd));
	// third_cmd
	cmd->pipeline.first_cmd->cmd.next->cmd.next->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv[0] = strdup("/bin/grep");
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv[1] = strdup("exe");
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.next = NULL;
	return (cmd);
}




