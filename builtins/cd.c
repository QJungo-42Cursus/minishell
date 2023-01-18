#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

static int	check_argv(char **argv)
{
	int		argc;

	while (argv[argc] != NULL)
		argc++;
	if (argc == 1)
	{
		// TODO cd ~ / cd home
		// Je crois qu'on est pas oblige de le faire ?
		return (SUCCESS);
	}
	if (argc > 2)
	{
		// TODO perror / errno
		printf("cd: too many arguments\n");
		return (ERROR);
	}
	return (SUCCESS);
}

int		cd(t_minishell *minishell, char **argv)
{
	// 0. check too many / too few arguments
	check_argv(argv);
	

	// 1. check with access if the path exists (relative or absolute)

	// 2. syscall to change the current working directory (chdir())
	// 3. change in env if exists (PWD=, and OLDPWD=)
	// 4. change minishell->current_working_directory
	//
	// bonus 4. actualize the prompt


	return (SUCCESS);
}
