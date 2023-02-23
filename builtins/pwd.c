#include "../minishell.h"
#include "../env/env.h"
#include "builtins.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <unistd.h>

int	pwd(t_minishell *minishell, char **argv)
{
	int		index;

	if (argv[1] != NULL)
	{
		write(2, "minishell: pwd: too many arguments\n", 35);
		return (ERROR);
	}
	index
		= get_env_var_index((const char **)minishell->env_copy, (char *)"PWD=");
	if (index != -1)
		printf("%s\n", minishell->env_copy[index] + 4);
	else
		printf("%s\n", minishell->current_working_directory);
	return (SUCCESS);
}
