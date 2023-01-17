#include "../libft/libft.h"
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <string.h>

/********************** utils ************************/

static int		pipe_index(int i, int read)
{
	return (i * 2 + read);
}

static int is_not_last(int i, int n)
{
	return (i < n - 1);
}

static int is_not_first(int i)
{
	return (i > 0);
}


/********************** execute_pipeline ************************/
#define READ 0
#define WRITE 1

static int init_pipes(int *pipes, int n)
{
	int i = 0;
	while (i < n)
	{
		if (pipe(&pipes[i * 2]) == -1)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}


static void	close_all_pipes(int *fds, int n)
{
	int		i;

	i = 0;
	while (i < n * 2)
	{
		close(fds[i]);
		i++;
	}
}

static int	init(int **pipes, int **pids, int args_list_size)
{
	*pipes = malloc(sizeof(int) * 2 * args_list_size);
	if (*pipes == NULL)
	{
		printf("malloc error\n");
		return (ERROR);
	}
	*pids = malloc(sizeof(int) * args_list_size);
	if (*pids == NULL)
	{
		printf("malloc error\n");
		free(*pipes);
		return (ERROR);
	}
	if (init_pipes(*pipes, args_list_size) == ERROR)
	{
		printf("malloc error\n");
		free(*pipes);
		free(*pids);
		return (ERROR);
	}
	return (SUCCESS);
}

// doesn't redirections
// doesn't handle signals (ctrl + c, ctrl + d)
int execute_simple_pipeline(char ***args_list, int args_list_size, char *envp[])
{
	int		*pipes;
	int		*pids;
	int		i;
	int		exit_code;

	init(&pipes, &pids, args_list_size);
	i = 0;
	while (i < args_list_size)
	{
		pids[i] = fork();
		//printf("forked %d\n", pids[i]);
		if (pids[i] == 0) /* CHILD */ 
		{
			if (is_not_last(i, args_list_size))
				dup2(pipes[pipe_index(i, WRITE)], STDOUT_FILENO);
			if (is_not_first(i))
				dup2(pipes[pipe_index(i - 1, READ)], STDIN_FILENO);
			close_all_pipes(pipes, args_list_size);

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
			execve(args_list[i][0], args_list[i], envp);

			exit(0);
			// TODO err handling
		}
		else
			i++;
	}
	wait(&exit_code);
	return (WEXITSTATUS(exit_code));
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	(void)argc;
	(void)envp;

	char ***args_list;
	args_list = malloc(sizeof(char **) * 3);
	args_list[0] = malloc(sizeof(char *) * 3);
	args_list[1] = malloc(sizeof(char *) * 3);
	args_list[2] = malloc(sizeof(char *) * 3);
	args_list[0][0] = strdup("/bin/ls");
	args_list[0][1] = strdup("-la");
	args_list[0][2] = NULL;
	args_list[1][0] = strdup("/bin/bc");
	args_list[1][1] = strdup("e");
	args_list[1][2] = NULL;
	args_list[2][0] = strdup("/bin/echo");
	args_list[2][1] = strdup("salut");
	args_list[2][2] = NULL;

	printf("will execute this command : %s %s | %s %s | %s %s\n",
			args_list[0][0], args_list[0][1], args_list[1][0], args_list[1][1], args_list[2][0], args_list[2][1]);

	printf("exit code: %d",	execute_simple_pipeline((char ***)args_list, 3, envp));
}
