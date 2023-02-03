#include "../libft/libft.h"
#include "../env/env.h"
#include "../builtins/builtins.h"
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
	return (argc);
}

static int	go_home(t_minishell *minishell)
{
	(void)minishell;


	// TODO  $HOME
	return (SUCCESS);
}

static int	export_pwd(t_minishell *minishell, const char *to_join)
{
	char	*joined_export_argv;
	char	**splited_export_argv;
	int		exit_code;

	joined_export_argv = ft_strjoin(to_join, minishell->current_working_directory);
	if (joined_export_argv == NULL)
		return (ERROR);
	splited_export_argv = ft_split(joined_export_argv, ' ');
	if (splited_export_argv == NULL)
	{
		free(joined_export_argv);
		return (ERROR);
	}
	exit_code = export_(minishell, splited_export_argv);
	free(joined_export_argv);
	split_free(splited_export_argv);
	return (exit_code);
}

static int	change_directory_in_env(t_minishell *minishell)
{
	if (get_env_var_index((const char **)minishell->env_copy, "OLDPWD=") != -1)
	{
		if (export_pwd(minishell, "export OLDPWD="))
			return (ERROR);
	}
	getcwd(minishell->current_working_directory, MAX_PATH_LEN + 1);
	if (get_env_var_index((const char **)minishell->env_copy, "PWD=") != -1)
	{
		if (export_pwd(minishell, "export PWD="))
			return (ERROR);
	}
	return (SUCCESS);
}

int		cd(t_minishell *minishell, char **argv)
{
	int		argc;

	argc = check_argv(argv);
	if (argc == -1)
		return (errno);
	if (argc == 1)
	{
		if (go_home(minishell) == -1)
			return (errno);
		return (SUCCESS);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("chdir:"); // TODO chdir ? cd ?
		return (errno);
	}
	if (change_directory_in_env(minishell) == ERROR)
	{
		// TODO best error handling ?
		return (ERROR);
	}
	refresh_prompt(minishell);
	return (SUCCESS);
}
