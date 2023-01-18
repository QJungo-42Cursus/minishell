#include "../minishell.h"
#include "../libft/libft.h"

int	env_var_index(t_minishell *mini, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = strlen_until(var, "=");
	while (mini->env_copy[i] != NULL)
	{
		if (ft_strncmp(mini->env_copy[i], var, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
