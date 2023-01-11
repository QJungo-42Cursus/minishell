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

typedef void (*t_get_token)(const char *str, int *index, int *start, int *end); // TODO trop d'args ? faire une struct ?

typedef struct s_token {
	char	*str;
	t_sep	sep;
	// TODO ajouter d'autre details, genre si les quotes sont fermes ou non
}	t_token;

void	get_token_dquote(const char *str, int *index, int *start, int *end);
void	get_token_quote(const char *str, int *index, int *start, int *end);
void	get_token_normal(const char *str, int *index, int *start, int *end);
void	get_token_pipe(const char *str, int *index, int *start, int *end); 
void	get_token_ampersant(const char *str, int *index, int *start, int *end);
void	get_token_semicolumn(const char *str, int *index, int *start, int *end);
void	get_token_greater(const char *str, int *index, int *start, int *end);
void	get_token_less(const char *str, int *index, int *start, int *end);

t_get_token	*list_func();
t_sep		get_sep(const char sep);
t_list		*tokenizer(const char *str);

//	debug helpers
void		log_tokens(t_list *tokens);
void		log_sep(t_sep sep);

#endif /* TOKENIZER_H */
