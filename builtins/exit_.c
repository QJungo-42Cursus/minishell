#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "builtins.h"

void	free_minishell(t_minishell *minishell)
{
	free(minishell->prompt_msg);
	split_free(minishell->env_copy);
}

int	exit_(t_minishell *minishell, char **argv, int exit_status)
{
	if (argv[1] != NULL)
	{
		// TODO same behavior in the main
		write(2, "minishell: pwd: too many arguments\n", 35);
		return (ERROR);
	}
	free_minishell(minishell);
	exit(exit_status);
	return (SUCCESS);
}
