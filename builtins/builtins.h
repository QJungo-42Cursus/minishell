/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:00:42 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/14 14:25:56 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../minishell.h"

int		echo(char **argv);
int		cd(t_minishell *minishell, char **argv);
int		pwd(t_minishell *minishell, char **argv);
int		env(t_minishell *minishell, char **argv);
int		export_(t_minishell *minishell, char **argv);
int		unset(t_minishell *minishell, char **argv);
int		exit_(t_minishell *minishell, char **argv, int exit_status);

#endif /* BUILTINS_H */
