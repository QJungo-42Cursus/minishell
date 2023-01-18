#include "../minishell.h"
#include "../env/env.h"
#include "builtins.h"
#include "../libft/libft.h"

int	pwd(t_minishell *minishell)
{
	if (env_var_index(minishell, "PWD="))
	{
	}
}
