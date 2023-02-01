#include "../minishell.h"
#include "../env/env.h"
#include "builtins.h"
#include "../libft/libft.h"

int	pwd(t_minishell *minishell, char **argv)
{
	(void)argv; // TODO check args
	if (get_env_var_index((const char **)minishell->env_copy, "PWD="))
	{
	}

	return (SUCCESS);
}
