#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "../libft/libft.h"
# include "../minishell.h"

t_list		*tokenizer(const char *cmd);
void		set_next_token_position(const char *cmd,
				int cursor_index, t_position *token_position);

#endif /* TOKENIZER_H */
