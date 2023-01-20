#ifndef EXPANSION_H
# define EXPANSION_H
# include "../minishell.h"

char		*expand(const char *token, const char **env_copy);
void		unquote(char *str);
int			get_var_position(int begin_from, const char *token, int *start_index, int *end_index);
char		*expand_dollar(const char *token, const char **env_copy, t_position index);

#endif /* EXPANSION_H */
