#include "../libft/libft.h"
#include "tokenizer.h"
#include "stdio.h"

void	get_token_normal(const char *str, int cursor_index, t_position *token_pos)
{
	t_position	quote_pos; // cpy pour pas modifier le start

	token_pos->start = cursor_index;
	while (str[cursor_index] != '\0' && !ft_isspace(str[cursor_index]))
	{
		if (str[cursor_index] == '\'' || str[cursor_index] == '"')
		{
			quote_pos.start = token_pos->start;
			get_token_quote(str, cursor_index, &quote_pos);
			token_pos->end = quote_pos.end;
			return ;
		}
		if (is_in_charset(str[cursor_index], "<>|&")) // TODO dollar ?
		{
			token_pos->end = cursor_index;
			return ;
		}
		cursor_index++;
	}
	token_pos->end = cursor_index;
}
