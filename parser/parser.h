#ifndef PARSER_H
# define PARSER_H
# include "../libft/libft.h"

/* TODO une idee pour pouvoir tout free a la fin : faire une list de t_list, 
 *		bien garder la taille, et free tout les elements qui ne sont pas NULL
 *		- en cas d'erreur : tout free
 *		- reussite : ne free que les t_list et pas les strings 
 */

typedef enum e_cmd_type {
	PIPELINE,		/* cmd | cmd | cmd | ... */
	COMMAND,		/* cmd */
	LOGIC_AND,		/* cmd && cmd */
	LOGIC_OR,		/* cmd || cmd */
	REDIR_IN,		/* < file cmd */
	REDIR_OUT,		/* cmd > file */
	REDIR_APPEND,	/* cmd >> file */
} t_cmd_type;

// la suite, juste pour le parser
enum e_token_type {
  OPEN_PARENTHESES = 7,
  CLOSE_PARENTHESES = 8,
};

enum e_result_more {
	USED = 2,
};

typedef struct s_cmd {
	t_cmd_type	type;
	union {
		// TODO simplify this
		struct {
			struct s_cmd *left;
			struct s_cmd *right;
		} logic;
		struct {
			struct s_cmd *left;
			struct s_cmd *right;
		} pipe;
		struct {
			char **argv;
			struct s_cmd *next; // only for pipeline
		} cmd;
		struct {
			int	*pipes;
			int *pids;
			int	pipe_count; // we could just count the count next commands
			struct s_cmd *first_cmd;
		} pipeline;
		struct {
			char *filename;
			int fd;
			struct s_cmd *cmd;
		} redir;
	};
} t_cmd;

t_list		*skip_parentheses(t_list *cursor);
int			get_token_type(char *token);
t_bool		are_we_in_parentheses(t_list *tokens);
t_list		*lst_cut_first_and_last(t_list *tokens);

int			parse_command(t_list *tokens, t_cmd *cmd);

int			set_command(t_list *tokens, t_cmd *cmd);

#endif /* PARSER_H */
