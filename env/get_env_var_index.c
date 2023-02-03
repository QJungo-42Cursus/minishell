#include "../minishell.h"
#include "../libft/libft.h"

#include <stdio.h>
int	get_env_var_index(const char **env_copy, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = strlen_until(var, "=");
	while (env_copy[i] != NULL)
	{
		if (ft_strncmp(env_copy[i], var, len) == 0 && env_copy[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
