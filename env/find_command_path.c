#include "../libft/libft.h"
#include <unistd.h>

/// --- find_path_line_in_env ---
/// * cmd_name : le nom du programme/script qu'on cherche | Non-null
/// * env_paths : les paths d'environnement | Non-null
/// return le path complet ou NULL si rien trouve | A free !
static char	*find_cmd_path_in_env(char *cmd_name, char **env_paths)
{
	int		i;
	char	*tmp_full_path;

	i = 0;
	while (env_paths[i] != 0)
	{
		// TODO la meme chose sans malloc a chaque fois ??
		tmp_full_path = ft_sprintf("%s/%s", env_paths[i], cmd_name);
		if (access(tmp_full_path, F_OK) == 0)
			return (tmp_full_path);
		free(tmp_full_path);
		i++;
	}
	return (NULL);
}

/// --- find_cmd_path ---
/// * cmd_name : le nom du programme/script qu'on cherche | Non-null
/// * env_paths : les paths d'environnement | Non-null
/// return le path complet | A free !
char	*find_cmd_path(char *cmd_name, char **env_paths)
{
	char	*full_path;

	full_path = find_cmd_path_in_env(cmd_name, env_paths);
	if (full_path != NULL)
		return (full_path);
	if (access(cmd_name, F_OK) == 0 && ft_strchr(cmd_name, '/'))
		return (ft_strdup(cmd_name));
	return (NULL);
}
