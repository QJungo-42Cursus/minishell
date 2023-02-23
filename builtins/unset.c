#include "../libft/libft.h"
#include "../minishell.h"
#include "../env/env.h"
#include <unistd.h>
#include <stdio.h>

static int	remove_env_var(t_minishell *minishell, int index_var)
{
	int		last;

	last = 0;
	while (minishell->env_copy[last] != NULL)
		last++;
	free(minishell->env_copy[index_var]);
	minishell->env_copy[index_var] = minishell->env_copy[last - 1];
	minishell->env_copy[last - 1] = NULL;
	return (SUCCESS);
}

int	unset(t_minishell *minishell, char **args)
{
	int		var_index;

	if (args[1] == NULL)
	{
		write(2, "unset: not enough arguments\n", 28);
		return (ERROR);
	}
	var_index = get_env_var_index((const char **)minishell->env_copy, args[1]);
	if (var_index == -1)
		return (SUCCESS);
	remove_env_var(minishell, var_index);
	return (SUCCESS);
}
