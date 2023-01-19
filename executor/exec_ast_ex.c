#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

typedef enum e_cmd_type {
	PIPELINE,		/* cmd | cmd | cmd | ... */
	COMMAND,		/* cmd */
	LOGIC_AND,		/* cmd && cmd */
	LOGIC_OR,		/* cmd || cmd */
	REDIR_IN,		/* < file cmd */
	REDIR_OUT,		/* cmd > file */
	REDIR_APPEND,	/* cmd >> file */
} t_cmd_type;

typedef struct s_cmd {
	t_cmd_type	type;
	union {
		// TODO simplify this
		struct {
			struct s_cmd *left;
			struct s_cmd *right;
		} logic;
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
			int *pids;
			int	pipe_count; // we could just count the count next commands
			struct s_cmd *first_cmd;
		} pipeline;
		struct {
			char *filename;
			int fd;
			struct s_cmd *cmd;
		} redir;
	};
} t_cmd;

int		pipe_index(int i, int read);
void	close_all_pipes(int *fds, int pipe_count);
int		fork1();

int	execute(t_cmd *cmd)
{
	int		exit_status;

	exit_status = 0;

	if (cmd->type == COMMAND)
	{
		if (fork1() == 0)
		{
			execvp(cmd->cmd.argv[0], cmd->cmd.argv);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
		wait(&exit_status);
	}

	else if (cmd->type == REDIR_IN || cmd->type == REDIR_OUT || cmd->type == REDIR_APPEND)
	{
		int		to_reopen;
		int		std_x_fileno;

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
			cmd->pipeline.pids[i] = fork();
			if (cmd->pipeline.pids[i] == 0)
			{
				if (i != 0) /* si c'est pas la premiere command */
					dup2(cmd->pipeline.pipes[pipe_index(i - 1, STDIN_FILENO)], STDIN_FILENO);
				if (i != cmd->pipeline.pipe_count - 1) /* si c'est pas la fin */
					dup2(cmd->pipeline.pipes[pipe_index(i, STDOUT_FILENO)], STDOUT_FILENO);
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
	}

	else if (cmd->type == LOGIC_AND || cmd->type == LOGIC_OR)
	{
		int left_exit_status = execute(cmd->logic.left);
		if (cmd->type == LOGIC_AND && left_exit_status == 0)
			exit_status = (execute(cmd->logic.right));
		else if (cmd->type == LOGIC_AND && left_exit_status != 0)
			exit_status = (left_exit_status);
		else if (cmd->type == LOGIC_OR && left_exit_status != 0)
			exit_status = (execute(cmd->logic.right));
		else if (cmd->type == LOGIC_OR && left_exit_status == 0)
			exit_status = (left_exit_status);
	}

	return (exit_status);
}

t_cmd	*init_example0();
t_cmd	*init_example1();
t_cmd	*init_example2();
t_cmd	*init_example3();
t_cmd	*init_example4();
t_cmd	*init_example5_logic();
t_cmd	*init_example6_redir();
t_cmd	*init_example7_redir_out();
t_cmd	*init_example8_redir_append();

int main()
{
	t_cmd	*cmd;
	int		exit_status;
	
	// TODO WEXITSTATUS(exit_status) pour recuperer le code de sortie !!!
	/*
	cmd = init_example0();
	exit_status = execute(cmd);
	printf("end example 0, exit_status : %d\n\n", exit_status);

	cmd = init_example1();
	exit_status = execute(cmd);
	printf("end example 1, exit_status : %d\n\n", exit_status);

	cmd = init_example2();
	exit_status = execute(cmd);
	printf("end example 2, exit_status : %d\n\n", exit_status);

	cmd = init_example3();
	exit_status = execute(cmd);
	printf("end example 3, exit_status : %d\n\n", exit_status);

	cmd = init_example4();
	exit_status = execute(cmd);
	printf("end example 4, exit_status : %d\n\n", exit_status);

	cmd = init_example5_logic();
	exit_status = execute(cmd);
	printf("exit status: %d\n", exit_status);

	cmd = init_example6_redir();
	exit_status = execute(cmd);
	printf("end example 6, exit_status : %d\n\n", exit_status);

	cmd = init_example7_redir_out();
	exit_status = execute(cmd);
	printf("end example 7, exit_status : %d\n\n", exit_status);
	*/

	cmd = init_example8_redir_append();
	exit_status = execute(cmd);
	printf("end example 8, exit_status : %d\n\n", exit_status);
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
	cmd->type = PIPELINE;
	cmd->pipeline.pipe_count = 2;
	cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->pipeline.pipes = malloc(sizeof(int) * 4);

	cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/ls");
	cmd->pipeline.first_cmd->cmd.argv[1] = strdup("-l");
	cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 2);
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/cat");
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = NULL;
	cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}

// example with pipeline
t_cmd	*init_example2()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = PIPELINE;
	cmd->pipeline.pids = malloc(sizeof(int) * 3);
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

// this one should fail
t_cmd	*init_example3()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = COMMAND;
	cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->cmd.argv[0] = strdup("/bin/bc");
	cmd->cmd.argv[1] = strdup("not_existing_file");
	cmd->cmd.argv[2] = NULL;
	return (cmd);
}

t_cmd	*init_example4()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = PIPELINE;
	cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->pipeline.pipe_count = 2;
	cmd->pipeline.pipes = malloc(sizeof(int) * 4);

	cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/echo");
	cmd->pipeline.first_cmd->cmd.argv[1] = strdup("salut");
	cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 2);
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/bc");
	cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = NULL;
	cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}

t_cmd	*init_example5_logic()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = LOGIC_OR;
	//cmd->logic.op = AND;
	cmd->logic.left = malloc(sizeof(t_cmd));
	cmd->logic.left->type = COMMAND;
	cmd->logic.left->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->logic.left->cmd.argv[0] = strdup("/bin/bc");
	cmd->logic.left->cmd.argv[1] = strdup("true 1");
	cmd->logic.left->cmd.argv[2] = NULL;
	cmd->logic.left->cmd.next = NULL;
	cmd->logic.right = malloc(sizeof(t_cmd));
	cmd->logic.right->type = COMMAND;
	cmd->logic.right->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->logic.right->cmd.argv[0] = strdup("/bin/echo");
	cmd->logic.right->cmd.argv[1] = strdup("true 2");
	cmd->logic.right->cmd.argv[2] = NULL;
	cmd->logic.right->cmd.next = NULL;
	return (cmd);
}

t_cmd	*init_example6_redir() 
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = REDIR_IN;
	cmd->redir.filename = strdup("test.txt");
	cmd->redir.cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->type = PIPELINE;
	cmd->redir.cmd->pipeline.pipe_count = 2;
	cmd->redir.cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->redir.cmd->pipeline.pipes = malloc(sizeof(int) * 4);
	cmd->redir.cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/cat");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[1] = strdup("-e");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/grep");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = strdup("exe");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}

t_cmd	*init_example7_redir_out()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = REDIR_OUT;
	cmd->redir.filename = strdup("test2.txt");
	cmd->redir.cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->type = PIPELINE;
	cmd->redir.cmd->pipeline.pipe_count = 2;
	cmd->redir.cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->redir.cmd->pipeline.pipes = malloc(sizeof(int) * 4);
	cmd->redir.cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/echo");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[1] = strdup("salut");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/cat");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = strdup("-e");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}

t_cmd	*init_example8_redir_append()
{
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->type = REDIR_APPEND;
	cmd->redir.filename = strdup("test2.txt");
	cmd->redir.cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->type = PIPELINE;
	cmd->redir.cmd->pipeline.pipe_count = 2;
	cmd->redir.cmd->pipeline.pids = malloc(sizeof(int) * 2);
	cmd->redir.cmd->pipeline.pipes = malloc(sizeof(int) * 4);
	cmd->redir.cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/echo");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[1] = strdup("salut append");
	cmd->redir.cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv = malloc(sizeof(char *) * 3);
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] = strdup("/bin/cat");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] = strdup("-e");
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
	cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
	return (cmd);
}
