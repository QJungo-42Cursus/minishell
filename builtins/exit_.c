#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "builtins.h"


int	exit_(t_minishell *minishell, char **argv, int exit_status)
{
	(void)argv; // TODO check args
	(void)minishell;

	// free_minishell(minishell); // TODO
	exit(exit_status);
	return (SUCCESS);
}
