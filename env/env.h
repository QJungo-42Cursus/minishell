#ifndef ENV_H
# define ENV_H

char	*find_cmd_path(char *cmd_name, char **env_paths);
char	**cpy_envp(char **envp);
char	**get_paths_in_env(char **envp);

#endif /* ENV_H */
