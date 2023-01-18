#include "../libft/libft.h"
#include "../minishell.h"
#include <errno.h>
#include <stdio.h>

static int	check_argv(char **argv)
{
	int		argc;

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	if (argc > 2)
	{
		errno = E2BIG;
		perror("cd:");
		return (-1);
	}
	return (SUCCESS);
}



static int	change_path(t_minishell *minishell, char *new_path)
{

}


static int	is_valid(char *new_path)
{

}

int		cd(t_minishell *minishell, char **argv)
{
	// 0. check too many / too few arguments
	int		exit_code;
	char	*path;
	exit_code = check_argv(argv);
	if (exit_code == -1)
		return (errno);

	if (exit_code == 1)
	{
		change_path(minishell, "~"); // TODO est-ce que ca marche ~
		return (SUCCESS);
	}

	t_bool	is_absolute;
	is_absolute = argv[1][0] == '/';



	change_path(minishell, "~"); // TODO est-ce que ca marche ~
		chdir("~");

	/*
		chdir(argv[1]);
	change_env(
	*/
	
	

	// 1. check with access if the path exists (relative or absolute)

	// 2. syscall to change the current working directory (chdir())
	// 3. change in env if exists (PWD=, and OLDPWD=)
	// 4. change minishell->current_working_directory
	//
	// bonus 4. actualize the prompt


	return (SUCCESS);
}
