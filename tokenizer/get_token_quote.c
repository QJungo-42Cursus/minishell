#include <stdio.h>
#include "../libft/libft.h"
#include "tokenizer.h"
#include "../tests/debug_helper.h"

int	is_last_char(const char *cmd, int cursor_index)
{
	if (cmd[cursor_index + 1] == '\0')
		return (TRUE);
	return (FALSE);
}

// TODO better name
// return true if it split the token after a quote/dquote
// (ex: ' echo ""salut ' renvoie FALSE, alors que ' echo "salut" ' renvoie TRUE)
int does_cut_string(const char c)
{
	if (ft_isspace(c))
		return (TRUE);
	if (is_in_charset(c, "$<>|&"))
		return (TRUE);
	return (FALSE);

	// TODO non printable ?
	if (!ft_isprint(c))
		return (TRUE);
}

/// Gere les simples quotes '
void	get_token_quote(const char *cmd, int cursor_index, t_position *token_pos)
{
	const char	sep = '\'';

	token_pos->start = cursor_index;

	//  TODO Vu que j'ai trim au debut, pas besoin de chercher apres ?
	if (is_last_char(cmd, cursor_index))
	{
		// TODO
		LOG("TODO: QUOTE not closed at end\n");
		token_pos->end = cursor_index; // +1 ?
		return ;
	}

	cursor_index++;

	// TODO inutile ? (gerer auto ?)
	/// Si les quotes sont fermées et vide, et que le char suivant est un espace
	/// on renvoie un token vide
	if (cmd[cursor_index] == sep && does_cut_string(cmd[cursor_index + 1]))
	{
		token_pos->end = cursor_index + 1;
		return ;
	}
	/// Si les quotes sont fermées et vide, et que le char suivant n'est pas un espace
	/// on continue
	// cursor_index += cmd[cursor_index] == sep; // facon style mais pas clair de faire plus 1
	if (cmd[cursor_index] == sep)
	{
		cursor_index++;
	}

	/// Sinon mode dquote "normal"
	while (cmd[cursor_index] != sep)
	{
		if (cmd[cursor_index] == '\0')
		{
			// TODO
			LOG("TODO: QUOTE not closed\n");
			token_pos->end = cursor_index;
			return ;
		}
		(cursor_index)++;
	}

	/// S'il reste du texte apres le quote, on le lit jusqu'a un isspace
	//if (!ft_isspace(cmd[cursor_index]) && cmd[cursor_index] != '\0')
	//	ft_strlcpy((char *)cmd + cursor_index, cmd + cursor_index + 1, ft_strlen(cmd + cursor_index));

	//while (!ft_isspace(cmd[cursor_index]) && cmd[cursor_index] != '\0')
	//	(cursor_index)++;
	token_pos->end = (cursor_index);
}




/// Gere les double quotes "
void	get_token_dquote(const char *cmd, int cursor_index, t_position *token_pos)
{
	/// Si c'est le dernier char -> error
	/// Vu que j'ai trim au debut, pas besoin de chercher apres
	if (cmd[cursor_index + 1] == '\0')
	{
		token_pos->start = -1;
		token_pos->end = -1;
		printf("TODO: DQUOTE not closed\n");
		return ;
	}

	/// Si les dquotes sont fermées et vide on renvoie un token vide
	cursor_index++;
	if (cmd[cursor_index] == '"')
	{
		token_pos->end = -1;
		token_pos->start = -1; // TODO c'est pas fait expres, mais quand je le met a 0, ca marche pas, le -1 marche
		cursor_index++;
		return ;
	}

	/// Sinon mode dquote "normal"
	(token_pos->start) = cursor_index;
	while (cmd[cursor_index] != '"')
	{
		/// Si on tombe sur un backslash, on skip le backslash pour afficher le char suivant
		/// Si c'etait un dquote, il va automatiquement le skip, apres le ft_strlcpy et le index++
		if (cmd[cursor_index] == '\\')
			ft_strlcpy((char *)cmd + cursor_index, cmd + cursor_index + 1, ft_strlen(cmd + cursor_index));
		if (cmd[cursor_index] == '\0')
		{
			// TODO s'il tombe sur le \0 avant le dqoute fermant, lire la prochaine ligne (comportement bash)
			printf("TODO: DQUOTE not closed\n");
			break ;
		}
		cursor_index++;
	}

	/// S'il reste du texte apres le quote, on le lit jusqu'a un isspace
	if (!ft_isspace(cmd[cursor_index]) && cmd[cursor_index] != '\0')
		ft_strlcpy((char *)cmd + cursor_index, cmd + cursor_index + 1, ft_strlen(cmd + cursor_index));
	while (!ft_isspace(cmd[cursor_index]) && cmd[cursor_index] != '\0')
		cursor_index++;

	(token_pos->end) = cursor_index;
}
