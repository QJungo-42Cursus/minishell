#include "../libft/libft.h"
#include "../env/env.h"
#include "../builtins/builtins.h"
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
		write(2, "minishell: cd: too many arguments\n", 34);
		return (-1);
	}
	return (argc);
}

static int	export_pwd(t_minishell *minishell, const char *to_join)
{
	char	*joined_export_argv;
	char	**splited_export_argv;
	int		exit_code;

	joined_export_argv
		= ft_strjoin(to_join, minishell->current_working_directory);
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
	if (get_env_var_index((const char **)minishell->env_copy,
			(char *)"OLDPWD=") != -1)
	{
		if (export_pwd(minishell, (char *)"export OLDPWD="))
			return (ERROR);
	}
	getcwd(minishell->current_working_directory, MAX_PATH_LEN + 1);
	if (get_env_var_index((const char **)minishell->env_copy,
			(char *)"PWD=") != -1)
	{
		if (export_pwd(minishell, (char *)"export PWD="))
			return (ERROR);
	}
	return (SUCCESS);
}

static int	change_dir(t_minishell *minishell, char *new_path)
{
	if (chdir(new_path) != 0)
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

static int	go_home(t_minishell *minishell)
{
	char	*home;

	home
		= get_env_var_value((char *)"HOME", (const char **)minishell->env_copy);
	if (home == NULL)
		return (ERROR);
	change_dir(minishell, home);
	free(home);
	return (SUCCESS);
}

int	cd(t_minishell *minishell, char **argv)
{
	int		argc;

	argc = check_argv(argv);
	if (argc == -1)
		return (errno);
	if (argc == 1)
		return (go_home(minishell));
	return (change_dir(minishell, argv[1]));
}
