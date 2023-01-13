#include <stdio.h>
#include "../libft/libft.h"
#include "tokenizer.h"
#include "../tests/debug_helper.h"

static int	is_last_char(const char *cmd, int cursor_index)
{
	if (cmd[cursor_index + 1] == '\0')
		return (TRUE);
	return (FALSE);
}

/// Gere les simples quotes ' et les doubles quotes "
void	get_token_quote(const char *cmd, int cursor_index, t_position *token_pos)
{
	char	sep;

	sep = cmd[cursor_index];

	token_pos->start = cursor_index;
	token_pos->end = cursor_index + 1;

	/// The quote is not closed (handle later)
	if (is_last_char(cmd, cursor_index))
		return ;

	cursor_index++;

	/// Si les quotes sont fermées et vide, et que le char suivant n'est pas un espace
	/// on continue
	if (cmd[cursor_index] == sep)
		cursor_index++;

	/// On cherche la fin de la quote
	while (cmd[cursor_index] != sep && cmd[cursor_index] != '\0')
		cursor_index++;
	/// On prend tout ce qu'il y a apres jusqu'a un espace // TODO autre sep ?
	while (!ft_isspace(cmd[cursor_index]) && cmd[cursor_index] != '\0')
		cursor_index++;
	token_pos->end = cursor_index;
}
