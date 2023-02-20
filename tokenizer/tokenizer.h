#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "../libft/libft.h"
# include "../minishell.h"

t_list		*tokenizer(const char *cmd, t_bool is_expand_mode);
void		set_next_token_position(const char *cmd,
				int cursor_index,
				t_position *token_position,
				t_bool is_expand_mode);

#endif /* TOKENIZER_H */
