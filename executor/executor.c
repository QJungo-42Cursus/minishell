#include "../libft/libft.h"
#include <unistd.h>
#include <wait.h>
#include <stdio.h>



int	execute_simple_command(char *argv[], char *envp[])
{
	int		pid;
	int		exit_code;

	pid = fork();
	if (pid == 0)
	{
		exit_code = execve(argv[0], argv, envp);
		return (exit_code); // va retourner -1 si erreur
	}
	waitpid(pid, &exit_code, 0);
	return (WEXITSTATUS(exit_code));
}


int main(int argc, char *argv[])
{
	char *envp[] = {NULL};

	int exit_code = execute_simple_command((char*[]){"/bin/ls", argv[1], NULL}, envp);
	printf("exit code = %d\n", exit_code);
	return (0);
}
