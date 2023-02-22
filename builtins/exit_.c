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
	(void)argv; // TODO check args
	(void)minishell;

	free_minishell(minishell);
	exit(exit_status);
	return (SUCCESS);
}
