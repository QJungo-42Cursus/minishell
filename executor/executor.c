#include "../libft/libft.h"
#include <unistd.h>
#include <wait.h>
#include <stdio.h>

int	execute_simple_command(char *argv[], char *envp[])
// prend en argv une liste VALIDE ! (access deja check)
// TODO juste une envp ?
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
