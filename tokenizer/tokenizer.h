#ifndef TOKENIZER_H

# include "../libft/libft.h"

# define TOKENIZER_H

# define SEP_NB 7
typedef enum e_sep
{
	QUOTE,
	DQUOTE,
	PIPE,
	AMPERSAND,
	SEMICOLUMN,
	GREATER,
	LESS,

	BACKSLASH, // parser direct la nouvelle ligne sans separer ???

	SEP_ERROR,
	NONE
} t_sep;

typedef void (*t_get_token)(char *str, int *index, int *start, int *end); // TODO trop d'args ? faire une struct ?

typedef struct s_token {
	char *str;
	t_sep sep;
}	t_token;

void	get_token_dquote(char *str, int *index, int *start, int *end);
void	get_token_quote(char *str, int *index, int *start, int *end);
void	get_token_normal(char *str, int *index, int *start, int *end);
void	get_token_pipe(char *str, int *index, int *start, int *end); 
void	get_token_ampersant(char *str, int *index, int *start, int *end);
void	get_token_semicolumn(char *str, int *index, int *start, int *end);
void	get_token_greater(char *str, int *index, int *start, int *end);
void	get_token_less(char *str, int *index, int *start, int *end);

t_get_token	*list_func();
t_sep		get_sep(char sep);
t_list		*tokenizer(char *str);

//	debug helpers
void		log_tokens(t_list *tokens);
void		log_sep(t_sep sep);

#endif /* TOKENIZER_H */
