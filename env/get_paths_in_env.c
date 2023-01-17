#include "../libft/libft.h"
#include <unistd.h>

static char	*find_path_line_in_env(char **envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL && (ft_strncmp(envp[i], "PATH=", 5) != 0))
		i++;
	if (envp[i] == NULL)
		return (NULL);
	return (envp[i] + 5);
}

char	**get_paths_in_env(char **envp)
{
	char	*path_line;

	path_line = find_path_line_in_env(envp);
	if (path_line)
		return (ft_split(path_line, ':'));
	return (NULL);
}
