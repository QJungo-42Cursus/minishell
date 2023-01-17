#ifndef EXECUTOR_H
# define EXECUTOR_H

char	**get_paths_in_env(char **envp);
char	*find_cmd_path(char *cmd_name, char **env_paths);

#endif /* EXECUTOR_H */
