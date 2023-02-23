#ifndef EXPANSION_H
# define EXPANSION_H
# include "../minishell.h"

char		*expand(const char *token, t_minishell *minishell);
void		unquote(char *str);
int			get_var_position(int begin_from,
				const char *token, int *start_index, int *end_index);
char		*expand_dollar(const char *token,
				t_minishell *minishell, t_position position);

#endif /* EXPANSION_H */
