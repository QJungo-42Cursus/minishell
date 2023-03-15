/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:50 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/15 11:53:10 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `"
# include "../libft/libft.h"

typedef enum e_cmd_type {
	PIPELINE,
	COMMAND,
	LOGIC_AND_deprecated,
	LOGIC_OR_deprecated,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
}	t_cmd_type;

enum e_result_more {
	USED = 2,
};

typedef struct s_cmd {
	t_cmd_type	type;
	union {
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
			int				fd;
			struct s_cmd	*cmd;
		} s_redir;
	};
}	t_cmd;

typedef struct s_cmd		t_cmd;
typedef struct s_minishell	t_minishell;

// parser_utils.c
int			get_token_type(char *token);

int			parse_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell);
int			pipeline(t_list *tokens, t_cmd *cmd, t_minishell *minishell);
int			set_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell);
t_cmd		*parser(t_list *tokens, t_minishell *minishell);

// free_ast.c
void		free_ast(t_cmd *cmd);

int			is_heredoc_valid(t_list *cursor, t_cmd *cmd);
int			get_heredoc(t_list **token_cursor, t_cmd *cmd);

int			redir(t_list *tokens, t_cmd *cmd, t_minishell *minishell);

// parse_redir_open.c
int			open_file(t_cmd *cmd, char *filename);
int			check_error(t_cmd *cmd, char *filename);

// parse_pipeline_utils.c
t_bool		is_pipe_alone(t_list *tokens);

#endif /* PARSER_H */
