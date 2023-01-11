#include "tokenizer.h"
#include "../libft/libft.h"
#include <stdio.h>

/*
 * TODO
 * ajouter un flag pour savoir si on est dans une quote ou une dquote
 * -> comme ca on peut savoir si l'ats va prendre en compte les $
 */

/// Return the separator type of the first char of the string
/// For the bash interpreter
t_sep	get_sep(char sep)
{
	if (sep == '&')
		return (AMPERSAND);
	if (sep == '|')
		return (PIPE);
	if (sep == ';')
		return (SEMICOLUMN);
	if (sep == '<')
		return (LESS);
	if (sep == '>')
		return (GREATER);
	if (sep == '\\')
		return (BACKSLASH);
	if (sep == '"')
		return (DQUOTE);
	if (sep == '\'')
		return (QUOTE);
	// retourne un NONE si c'est un char normal
	if (ft_isprint(sep))
		return (NONE);
	// TODO: gérer les non-printable chars ??
	//return (-1);
	return (SEP_ERROR);
}

t_get_token	*list_func()
{
	t_get_token	*list;

	list = (t_get_token *)malloc(sizeof(t_get_token) * SEP_NB);
	if (list == NULL)
	{
		// TODO
		return (NULL);
	}
	list[DQUOTE] = get_token_dquote;
	list[NONE] = get_token_normal;
	list[QUOTE] = get_token_quote;
	list[PIPE] = get_token_pipe;
	list[AMPERSAND] = get_token_ampersant;
	list[SEMICOLUMN] = get_token_semicolumn;
	list[GREATER] = get_token_greater;
	list[LESS] = get_token_less;
	return (list);
}
