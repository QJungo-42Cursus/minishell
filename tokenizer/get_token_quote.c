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

// TODO better name
// return true if it split the token after a quote/dquote
// (ex: ' echo ""salut ' renvoie FALSE, alors que ' echo "salut" ' renvoie TRUE)
static int does_cut_string_litteral(const char c)
{
	if (ft_isspace(c))
		return (TRUE);
	if (is_in_charset(c, "$<>|&"))
		return (TRUE);
	if (c == '\0')
		return (TRUE);
	return (FALSE);

	// TODO non printable ?
	if (!ft_isprint(c))
		return (TRUE);
}

/// Gere les simples quotes '
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

	// TODO inutile ? (gerer auto ?)
	/// Si les quotes sont fermées et vide, et que le char suivant est un espace
	/// on renvoie un token vide
	if (cmd[cursor_index] == sep && does_cut_string_litteral(cmd[cursor_index + 1]))
	{
		token_pos->end = cursor_index + 1;
		return ;
	}

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
