#include "tokenizer.h"
#include "../libft/libft.h"
#include <stdio.h>

/// Return the separator type of the first char of the string
/// For the bash interpreter
t_sep	get_sep(char sep)
{
	int		i;
	char	separators[SEP_NB];

	separators[DQUOTE] = '"';
	separators[QUOTE] = '\'';
	separators[PIPE] = '|';
	separators[AMPERSAND] = '&';
	separators[GREATER] = '>';
	separators[LESS] = '<';
	// ft_strlcpy(separators, "\"'&|><", SEP_NB); // TODO -> avec le bon ordre !
	i = 0;
	while (i < SEP_NB)
	{
		if (sep == separators[i])
			return ((t_sep)i);
		i++;
	}
	// retourne un NONE si c'est un char normal
	if (ft_isprint(sep))
		return (NONE);
	// TODO: gérer les non-printable chars ??
	//return (-1);
	return (SEP_ERROR);
}

void	generic_get_token(const char *cmd, int cursor_index, t_position *token_pos)
{
	char	c;

	// FIXME -> gestion d'exeption
	// ex: "2>" -> vont dans le meme token
	// ex: "&2>" -> vont dans le meme token -> ca depend de si on doit gerer le async ou pas
	c = cmd[cursor_index];
	token_pos->start = cursor_index;
	while (cmd[cursor_index] != '\0' && cmd[cursor_index] == c)
		cursor_index++;
	token_pos->end = cursor_index;
}

t_set_token_position	*list_func(void)
{
	// TODO !! Add ` and $ to the list
	t_set_token_position	*list;

	list = (t_set_token_position *)malloc(sizeof(t_set_token_position) * SEP_NB);
	if (list == NULL)
	{
		// TODO
		return (NULL);
	}
	// specific
	list[DQUOTE] = get_token_quote;// get_token_quote; // TODO c'est 2x le meme, facto ?
	list[QUOTE] = get_token_quote;
	list[NONE] = get_token_normal;

	// generic
	list[PIPE] = generic_get_token;
	list[AMPERSAND] = generic_get_token;
	list[GREATER] = generic_get_token;
	list[LESS] = generic_get_token;

	// bonus
	//list[SEMICOLUMN] = get_token_semicolumn;
	//list[BACKSLASH] = get_token_backslash;
	return (list);
}
