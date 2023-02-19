#include <stdlib.h>
#include "../libft/libft.h"

char	**cpy_envp(char **envp)
{
	int i;
	char **env_copy;

	i = 0;
	while (envp[i])
		i++;
	env_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (env_copy[i] == NULL)
		{
			i--;
			while (i >= 0)
				free(env_copy[i--]);
			free(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
