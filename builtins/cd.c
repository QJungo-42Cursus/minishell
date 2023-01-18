#include "../libft/libft.h"
#include "../minishell.h"
#include <unistd.h>
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

int		cd(t_minishell *minishell, char **argv)
{
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

	if (chdir(argv[1]) != 0)
	{
		perror("chdir:");
		return (errno);
	}
	if (get_env_var_index(minishell->env_copy, "OLD_PWD=") != -1)
	{

		path = ft_strjoin("OLD_PWD=", minishell->current_working_directory);
	}
	getcwd(minishell->current_working_directory, 4097);
	if (get_env_var_index(minishell->env_copy, "PWD="))
	{}

	
	

	// 1. check with access if the path exists (relative or absolute)

	// 2. syscall to change the current working directory (chdir())
	// 3. change in env if exists (PWD=, and OLDPWD=)
	// 4. change minishell->current_working_directory
	//
	// bonus 4. actualize the prompt


	return (SUCCESS);
}
