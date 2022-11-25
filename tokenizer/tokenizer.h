#ifndef TOKENIZER_H

# include "../libft/libft.h"

# define TOKENIZER_H

# define SEP_NB 5
typedef enum e_sep
{
	QUOTE,
	DQUOTE,
	PIPE,
	AMPERSAND,
	SEMICOLUMN,

	BACKSLASH,
	GREATER,
	LESS,

	SEP_ERROR,
	NONE
} t_sep;

typedef void (*t_get_token)(char *str, int *index, int *start, int *end); // TODO trop d'args ?


t_get_token	*list_func();
t_sep		get_sep(char sep);
t_list		*tokenizer(char *str);

//	debug helpers
void		log_tokens(t_list *tokens);
void		log_sep(t_sep sep);

#endif /* TOKENIZER_H */
