/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:42:45 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/14 17:16:21 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PATH_LEN 4096
# include "parser/parser.h"
# include <signal.h>

typedef struct s_cmd	t_cmd;

// TODO set exito -1 ?
typedef enum e_minishell_status {
	S_EXEC,
	S_EXEC_ABORT,
	S_PROMPT,
	S_HEREDOC,
	S_HEREDOC_ABORT,
}	t_minishell_status;

typedef struct s_minishell {
	char				*prompt_msg;
	char				current_working_directory[MAX_PATH_LEN];
	char				**env_copy;
	int					last_exit_status;
	int					should_exit;
	t_cmd				*current_ast;
	void				**tokens_to_free;
}	t_minishell;

typedef struct s_position
{
	int		start;
	int		end;
}	t_position;

void	append_to_free_list(t_minishell *minishell, t_list *to_append);
int		init_minishell(t_minishell *minishell, char **envp);
void	refresh_prompt(t_minishell *minishell);
void	malloc_error(t_minishell *minishell);
void	signal_handler(int sig);
int		main_loop(t_minishell *minishell);

#endif /* MINISHELL_H */
