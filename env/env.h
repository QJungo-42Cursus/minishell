#ifndef ENV_H
# define ENV_H

#include "../minishell.h"

char	*find_cmd_path(char *cmd_name, char **env_paths);
char	**cpy_envp(char **envp);
char	**get_paths_in_env(char **envp);
int		get_env_var_index(const char **env_copy, char *var);
char	*get_env_var_value(char *var_name, const char **env_copy);

#endif /* ENV_H */
