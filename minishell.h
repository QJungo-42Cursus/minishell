/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:42:45 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 19:39:56 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PATH_LEN 4096
# include "parser/parser.h"
# include <signal.h>

typedef struct s_cmd	t_cmd;

typedef struct s_minishell {
	char	*prompt_msg;
	char	current_working_directory[MAX_PATH_LEN];
	char	**env_copy;
	int		last_exit_status;
	int		should_exit;
	t_cmd	*current_ast;
	struct sigaction	*m_exec_sa;
}	t_minishell;

typedef struct s_position
{
	int		start;
	int		end;
}	t_position;

int		init_minishell(t_minishell *minishell, char **envp);
void	refresh_prompt(t_minishell *minishell);
void	malloc_error(t_minishell *minishell);

#endif /* MINISHELL_H */
