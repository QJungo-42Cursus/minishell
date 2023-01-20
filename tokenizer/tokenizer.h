#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../libft/libft.h"
# include "../minishell.h"
# define SEP_NB 6

typedef enum e_sep
{
	QUOTE,
	DQUOTE,
	PIPE,
	AMPERSAND,
	GREATER,
	LESS,
	NONE,
} t_sep;


typedef void (*t_set_token_position)(const char *str, int cursor_index, t_position *token_pos);

typedef struct s_token {
	char	*str;
	t_sep	sep;
	// TODO ajouter d'autre details, genre si les quotes sont fermes ou non
}	t_token;

// TODO rename to "set_token_pos_x"
void	get_token_dquote	(const char *str, int cursor_index, t_position *token_pos);
void	get_token_quote		(const char *str, int cursor_index, t_position *token_pos);
void	get_token_normal	(const char *str, int cursor_index, t_position *token_pos);

t_set_token_position	*list_func(void);
t_sep		get_sep(const char sep);
t_list		*tokenizer(const char *cmd);




int	set_next_token_position(const char *cmd, int cursor_index, t_set_token_position *set_token_position, t_position *token_position);

#endif /* TOKENIZER_H */
