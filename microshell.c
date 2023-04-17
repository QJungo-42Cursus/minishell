
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

static void ft_putstr(int fd, char *str)
{
	int i = 0;
	while (str[i] != 0)
	{
		write(fd, &str[i], 1);
		i++;
	}
}

static int fork1()
{
	int pid = fork();
	if (pid == -1)
	{
		ft_putstr(2, "error: fatal\n");
		exit(1);
	}
	return pid;
}

static void p_error(char *prog)
{
	ft_putstr(2, "error: cannot execute ");
	ft_putstr(2, prog);
	ft_putstr(2, "\n");
}

static int pipe_exec(char **argv, char **envp)
{
	int pids[2048];
	int cmd_argc = 0;
	int is_first = 1;
	int to_add = 0;
	int ip = 0;
	int current_pipe[2];
	int last_pipe[2];

	while (1)
	{
		if (argv[cmd_argc] == NULL || strncmp(argv[cmd_argc], ";", 2) == 0)
		{
			pids[ip] = fork1();
			if (pids[ip] == 0)
			{
				argv[cmd_argc] = NULL;
				dup2(last_pipe[STDIN_FILENO], STDIN_FILENO);
				close(last_pipe[0]);
				close(last_pipe[1]);
				execve(argv[0], argv, envp);
				p_error(argv[0]);
				exit(1);
			}
			close(last_pipe[0]);
			close(last_pipe[1]);
			break;
		}
		if (strncmp(argv[cmd_argc], "|", 2) == 0)
		{
			if (pipe(current_pipe) == -1)
			{
				ft_putstr(2, "error: fatal\n");
				exit(1);
			}
			pids[ip] = fork1();
			if (pids[ip] == 0)
			{
				argv[cmd_argc] = NULL;
				if (!is_first)
					dup2(last_pipe[STDIN_FILENO], STDIN_FILENO);
				dup2(current_pipe[STDOUT_FILENO], STDOUT_FILENO);

				close(current_pipe[0]);
				close(current_pipe[1]);
				if (!is_first)
				{
					close(last_pipe[0]);
					close(last_pipe[1]);
				}

				execve(argv[0], argv, envp);
				p_error(argv[0]);
				exit(1);
			}
			if (!is_first)
			{
				close(last_pipe[0]);
				close(last_pipe[1]);
			}
			last_pipe[0] = current_pipe[0];
			last_pipe[1] = current_pipe[1];
			is_first = 0;
			argv = &argv[cmd_argc + 1];
			to_add++;
			ip++;
			cmd_argc = 0;
		}
		cmd_argc++;
		to_add++;
	}
	for (int y = 0; y < ip; y++)
		waitpid(pids[y], NULL, 0);
	return to_add;
}

void exec(int argc, char **argv, char **envp)
{
	if (strncmp(argv[0], "cd", 3) == 0)
	{
		if (argc != 2)
		{
			ft_putstr(2, "error: cd: bad arguments\n");
			return ;
		}
		if (chdir(argv[1]) == -1)
		{
			ft_putstr(2, "error: cd: cannot change directory to ");
			ft_putstr(2, argv[1]);
			ft_putstr(2, "\n");
			return ;
		}
		return ;
	}
	int pid = fork1() ;
	if (pid == 0)
	{
		argv[argc] = NULL;
		execve(argv[0], argv, envp);
		p_error(argv[0]);
		exit(1);
	}
	waitpid(pid, NULL, 0);
}

int main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		return 1;
	argv++;
	int cmd_argc = 0;

	while(1)
	{
		if (argv[cmd_argc] == NULL || strncmp(argv[cmd_argc], ";", 2) == 0)
		{
			exec(cmd_argc, argv, envp);
			if (argv[cmd_argc] == NULL || argv[cmd_argc + 1] == NULL)
				break;
			argv = &argv[cmd_argc + 1];
			cmd_argc = 0;
		}
		if (strncmp(argv[cmd_argc], "|", 2) == 0)
		{
			int to_add = pipe_exec(argv, envp);

			if (argv[to_add] == NULL)
				break;
			argv = &argv[to_add + 1];
			cmd_argc = 0;
			if (argv[0] == NULL)
				break;
		}
		cmd_argc++;
	}
}
