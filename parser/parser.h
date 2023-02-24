/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:50 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 14:33:34 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `"
# include "../minishell.h"
# include "../libft/libft.h"

typedef enum e_cmd_type {
	PIPELINE,
	COMMAND,
	LOGIC_AND,
	LOGIC_OR,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
}	t_cmd_type;

// la suite, juste pour le parser
enum e_token_type {
	OPEN_PARENTHESES = 10,
	CLOSE_PARENTHESES,
};

enum e_result_more {
	USED = 2,
};

typedef struct s_cmd {
	t_cmd_type	type;
	union {
		struct {
			struct s_cmd	*left;
			struct s_cmd	*right;
		} s_logic;
		struct {
			char			**argv;
			char			*heredoc;
			struct s_cmd	*next;
		} s_command;
		struct {
			int				*pipes;
			int				*pids;
			int				pipe_count;
			struct s_cmd	*first_cmd;
		} s_pipeline;
		struct {
			char			*filename;
			int				fd;
			struct s_cmd	*cmd;
		} s_redir;
	};
}	t_cmd;

typedef struct s_cmd		t_cmd;
typedef struct s_minishell	t_minishell;

t_list		*skip_parentheses(t_list *cursor);
int			get_token_type(char *token);
t_bool		are_we_in_parentheses(t_list *tokens);
t_list		*lst_cut_first_and_last(t_list *tokens);

int			parse_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell);
int			pipeline(t_list *tokens, t_cmd *cmd, t_minishell *minishell);
int			set_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell);
t_cmd		*parser(t_list *tokens, t_minishell *minishell);

void		free_ast(t_cmd *cmd);

int			is_heredoc_valid(t_list *cursor, t_cmd *cmd);
int			get_heredoc(t_list **token_cursor, t_cmd *cmd);

#endif /* PARSER_H */
