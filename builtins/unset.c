#include "../libft/libft.h"
#include "../minishell.h"
#include "../env/env.h"

static int	remove_env_var(t_minishell *mini, int index_var)
{
	int		last;

	last = 0;
	while (mini->env_copy[last] != NULL)
		last++;
	free(mini->env_copy[index_var]);
	mini->env_copy[index_var] = mini->env_copy[last - 1];
	mini->env_copy[last - 1] = NULL;
	return (SUCCESS);
}

int	unset(t_minishell *minishell, char **args)
{
	char	*var;
	int		var_index;

	var = ft_strjoin(args[1], "=");
	if (var == NULL)
		return (ERROR);
	var_index = env_var_index(minishell, var);
	if (var_index != -1)
		remove_env_var(minishell, var_index);
	free(var);
	return (SUCCESS);
}

