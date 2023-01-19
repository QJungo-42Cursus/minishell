#include <stdlib.h>
#include "../minishell.h"
#include "../libft/libft.h"
#include "env.h"

// return ownership
char *get_env_var_value(char *var_name, const char **env_copy) 
{
	int		env_index;
	char	*value_start;

	env_index = get_env_var_index(env_copy, var_name);
	if (env_index == -1)
		return (NULL);
	value_start = ft_strchr((char *)env_copy[env_index], '=') + 1;
	if (value_start == NULL)
		return (NULL);
	return (ft_strdup(value_start));
}
