#include "executor.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

#define BUFFER_SIZE 2048

const char * FILE_IN = "./file_in";
const char * FILE_OUT = "./file_out";

void	files()
{
	/*
	int infile_fd = open(FILE_IN, O_RDONLY);
	int outfile_fd = open(FILE_OUT, O_TRUNC | O_CREAT | O_RDWR, 0000644); // TODO si mode >> append au lieu de O_TRUNC
	if (infile_fd == -1)
	{
		perror("pipex: input");
	}
	if (outfile_fd == -1)
	{
		perror("pipex: input");
	}

	execve("/bin/ls", NULL, NULL);
	*/
}

void	example1()
{

	int pipefd_a[2];

	pipe(pipefd_a);

	int pid = fork();
	if (pid == -1)
	{
		perror("caca");
		return ;
	}
	if (pid == 0) /* CHILD */
	{
		close(pipefd_a[0]);
		dup2(pipefd_a[1], STDOUT_FILENO);
		sleep(1);
		write(STDOUT_FILENO, "coucou from child\n", 18);
		close(pipefd_a[1]);
	}
	else /* PARENT */
	{
		printf("on est dans le parent\n");
		char buf[BUFFER_SIZE];
		// Le read va nous faire attendre tant
		// qu'il n'y a pas de données dans le pipe
		int count = read(pipefd_a[0], buf, BUFFER_SIZE);
		buf[count] = '\0';
		printf("buf: %s\n", buf);
		close(pipefd_a[0]);
		close(pipefd_a[1]);
	}
}

void	example2()
{

	int pipefd_a[2]; // de 0 a 1
	pipe(pipefd_a);

	int pipefd_b[2]; // de 1 a 2
	pipe(pipefd_b);

	int pipefd_c[2]; // de 2 a 3
	pipe(pipefd_c);

	int pid = fork();
	if (pid != 0) /* PARENT */
	{
		int pid2 = fork();
		if (pid2 != 0) /* PARENT */
		{
			int pid3 = fork();
			if (pid3 != 0) /* PARENT */
			{
				close(pipefd_a[0]);
				close(pipefd_a[1]);
				close(pipefd_b[0]);
				close(pipefd_b[1]);
				close(pipefd_c[1]);
				printf("on est dans le parent\n");
				char buf[BUFFER_SIZE];
				// Le read va nous faire attendre tant
				// qu'il n'y a pas de données dans le pipe
				int count = read(pipefd_c[0], buf, BUFFER_SIZE);
				close(pipefd_c[0]);
				buf[count] = '\0';
				printf("buf: %s\n", buf);
			}
			else /* CHILD 3 */
			{
				close(pipefd_a[0]);
				close(pipefd_a[1]);
				close(pipefd_b[1]);
				close(pipefd_c[0]);

				char *args[] = {"/bin/grep", "exe", NULL};
				dup2(pipefd_b[0], STDIN_FILENO);
				dup2(pipefd_c[1], STDOUT_FILENO);

				close(pipefd_c[1]);
				close(pipefd_b[0]);
				execve("/bin/grep", args, NULL);
			}
		}
		else /* CHILD 2 */
		{
			close(pipefd_c[0]);
			close(pipefd_c[1]);
			close(pipefd_a[1]);
			close(pipefd_b[0]);

			char *args[] = {"/bin/cat", "-e", NULL};
			dup2(pipefd_a[0], STDIN_FILENO);
			dup2(pipefd_b[1], STDOUT_FILENO);

			close(pipefd_a[0]);
			close(pipefd_b[1]);
			execve("/bin/cat", args, NULL);
		}
	}
	else /* CHILD 1 */
	{
		dup2(pipefd_a[1], STDOUT_FILENO);

		close(pipefd_c[0]);
		close(pipefd_c[1]);
		close(pipefd_b[0]);
		close(pipefd_a[0]);
		close(pipefd_a[1]);
		close(pipefd_b[1]);
		execve("/bin/ls", NULL, NULL);
	}
}



void	close_all(int *fds, int n)
{
	int i = 0;
	while (i < n)
	{
		close(fds[i]);
		i++;
	}
}

#define READ 0
#define WRITE 1
#define PIPE_COUNT 3

int		pipe_index(int i, int read)
{
	return (i * 2 + read);
}
void	close_all_pipes(int *fds)
{
	int i = 0;
	while (i < PIPE_COUNT * 2)
	{
		close(fds[i]);
		i++;
	}
}

void	example3()
{
	//int pipes[PIPE_COUNT][2];
	int (*pipes_heap)[2] = malloc(sizeof(int) * 2 * PIPE_COUNT);

	int contiguos_pipefds[PIPE_COUNT * 2];
	pipe(&contiguos_pipefds[pipe_index(0, 0)]); //a
	pipe(&contiguos_pipefds[pipe_index(1, 0)]); //b
	pipe(&contiguos_pipefds[pipe_index(2, 0)]); //c


	int pid = fork();
	if (pid != 0) /* PARENT */
	{
		int pid2 = fork();
		if (pid2 != 0) /* PARENT */
		{
			int pid3 = fork();
			if (pid3 != 0) /* PARENT */
			{
				const int B_SIZE = 3;
				printf("on est dans le parent\n");
				char buf[B_SIZE];
				// Le read va nous faire attendre tant
				// qu'il n'y a pas de données dans le pipe
				//int count = read(contiguos_pipefds[pipe_index(2, READ)], buf, B_SIZE);
				close_all_pipes(contiguos_pipefds);
				//buf[count] = '\0';
				//printf("buf: %s\n", buf);
			}
			else /* CHILD 3 */
			{
				printf("on est dans le fils 3\n");
				char *args[] = {"/bin/grep", "exe", NULL};
				//dup2(contiguos_pipefds[pipe_index(2, WRITE)], STDOUT_FILENO);
				dup2(contiguos_pipefds[pipe_index(1, READ)], STDIN_FILENO);
				close_all_pipes(contiguos_pipefds);
				execve("/bin/grep", args, NULL);
				printf("execve failed\n");
			}
		}
		else /* CHILD 2 */
		{
			char *args[] = {"/bin/cat", "-e", NULL};
			dup2(contiguos_pipefds[pipe_index(1, WRITE)], STDOUT_FILENO);
			dup2(contiguos_pipefds[pipe_index(0, READ)], STDIN_FILENO);
			close_all_pipes(contiguos_pipefds);
			execve("/bin/cat", args, NULL);
		}
	}
	else /* CHILD 1 */
	{
		char *args[] = {"/bin/ls", "-la",  NULL};
		dup2(contiguos_pipefds[pipe_index(0, WRITE)], STDOUT_FILENO);
		close_all_pipes(contiguos_pipefds);
		execve("/bin/ls", args, NULL);
	}
}

void	init_pipes(int *pipes, int n)
{
	int i = 0;
	while (i < n)
	{
		pipe(&pipes[i * 2]);
		i++;
	}
}

// TODO comment avoir le exit status du processus fils ?
void	example4()
{
	int contiguos_pipefds[PIPE_COUNT * 2];
	int exit_code_pipe[2];
	pipe(exit_code_pipe);
	init_pipes(contiguos_pipefds, PIPE_COUNT);
	char *all_args[3][3] = {
		{"/bin/ls", "-la",  NULL},
		{"/bin/cat", "-e", NULL},
		{"/bin/bc", "e", NULL}
		//{"/bin/grep", "e", NULL}
	};
	int i = 0;




	int pid = fork();
	int pids[PIPE_COUNT] = {0,0,0};
	if (pid == 0) /* CHILD */ // where all the execve are lauched
	{
		while (i < PIPE_COUNT)
		{
			pids[i] = fork();
			// On note que si on inverse et qu'on se met dans l'enfant,
			// vu que les deux sont bien sepate par la condition,
			// on obtient le meme resultat
			if (pids[i] == 0) /* CHILD */ 
			{
				if (i == 0) /* si c'est la premiere command */
				{
					//dup2(exit_code_pipe[WRITE], FD_CLOEXEC);
					dup2(contiguos_pipefds[pipe_index(i, WRITE)], STDOUT_FILENO);
					close_all_pipes(contiguos_pipefds);
					execve(all_args[i][0], all_args[i], NULL);

					printf("execve failed\n");
					exit(2);
				}
				else if (i == PIPE_COUNT - 1) /* si c'est la fin */
				{
					//dup2(exit_code_pipe[WRITE], FD_CLOEXEC);
					dup2(contiguos_pipefds[pipe_index(i - 1, READ)], STDIN_FILENO);
					close_all_pipes(contiguos_pipefds);
					execve(all_args[i][0], all_args[i], NULL);

					printf("execve failed\n");
					exit(2);
				}
				else /* si c'est au milieu */
				{
					//dup2(exit_code_pipe[WRITE], FD_CLOEXEC);
					dup2(contiguos_pipefds[pipe_index(i - 1, READ)], STDIN_FILENO);
					dup2(contiguos_pipefds[pipe_index(i, WRITE)], STDOUT_FILENO);
					close_all_pipes(contiguos_pipefds);
					execve(all_args[i][0], all_args[i], NULL);

					printf("execve failed\n");
					exit(2);
				}
			}
			else /* CHILD */
			{
				i++;
			}
		} /* end while */
		
		int exit_code;
		wait(&exit_code);
		for(int i = 0; i < PIPE_COUNT; i++)
		{
			printf("pids[%d]: %d\n", i, pids[i]);
			//waitpid(pids[i], &exit_code, 0);
		}
		//exit_code = 444;
		write(exit_code_pipe[WRITE], &exit_code, sizeof(int));
	}
	else
	{
		printf("on est dans le parent (le vrai, le main)\n");
		int exit_code;
		waitpid(pid, &exit_code, 0);
		read(exit_code_pipe[READ], &exit_code, sizeof(int));
		printf("exit code = %d\n", WEXITSTATUS(exit_code));

	}
}




void	example5()
{
	// passing a int into a pipe
	int pipefd[2];
	pipe(pipefd);
	int pid = fork();
	if (pid == 0) /* CHILD */
	{
		int i = 478;
		write(pipefd[WRITE], &i, sizeof(int));
	}
	else /* PARENT */
	{
		int result;
		read(pipefd[READ], &result, sizeof(int));
		printf("result: %d\n", result);
	}
}

int main()
{
	//example1();
	//example2();
	//example3();
	example4();
	//example5();
}

// STDIN_FILENO = 0
// STDOUT_FILENO = 1
// STDERR_FILENO = 2
// dup2(fd_a <= fd_b) renvoie fd_b dans fd_a
// pipefd[0] = read
// pipefd[1] = write
