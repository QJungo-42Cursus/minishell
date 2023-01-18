#include "../libft/libft.h"
#include "../env/env.h"
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
	int		argc;
	char	*path;
	argc = check_argv(argv);
	if (argc == -1)
		return (errno);

	if (argc == 1)
	{
		// TODO  $HOME
		return (SUCCESS);
	}

	if (argv[1][0] == '~') // on ne doit pas gerer les symlink
	{
		// TODO
		return (SUCCESS);
	}

	if (chdir(argv[1]) != 0)
	{
		perror("chdir:");
		return (errno);
	}
	if (get_env_var_index(minishell->env_copy, "OLD_PWD=") != -1)
	{
		// TODO rename
		char * new_paths_arg = ft_strjoin("export OLD_PWD=", minishell->current_working_directory);
		char ** new_paths = ft_split(new_paths_arg, ' ');
		if (export_(minishell, new_paths))
		{
			// TODO
		}
	}
	getcwd(minishell->current_working_directory, 4097);
	if (get_env_var_index(minishell->env_copy, "PWD=") != -1)
	{
		// TODO rename
		char * new_paths_arg = ft_strjoin("export PWD=", minishell->current_working_directory);
		char ** new_paths = ft_split(new_paths_arg, ' ');
		if (export_(minishell, new_paths))
		{
			// TODO
		}
	}
	// bonus 4. actualize the prompt
	return (SUCCESS);
}
