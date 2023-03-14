/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:18:10 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/14 14:25:54 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H
# include "../minishell.h"

char	*find_cmd_path(char *cmd_name, char **env_paths);
char	**cpy_envp(char **envp);
int		print_all_env(t_minishell *minishell);
char	**get_paths_in_env(char **envp);
int		get_env_var_index(const char **env_copy, char *var);
char	*get_env_var_value(char *var_name, const char **env_copy);
char	*find_cmd_path(char *cmd_name, char **env_paths);

#endif /* ENV_H */
