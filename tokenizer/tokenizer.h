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
} t_sep;

typedef void (*t_get_token)(char *str, int *index);


t_get_token	*list_func();
t_sep		get_sep(char sep);
t_list		*tokenizer(char *str);

#endif /* TOKENIZER_H */
