#include "tokenizer.h"
#include "../libft/libft.h"

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
	return (-1);
}

void	get_token_quote(char *str, int *index)
{
	(void)str;
	(void)index;
}

void	get_token_dquote(char *str, int *index)
{
	(void)str;
	(void)index;
}

void	get_token_pipe(char *str, int *index) // TODO autre term tech ?
{
	(void)str;
	(void)index;
}

void	get_token_ampersant(char *str, int *index) // TODO ortho
{
	(void)str;
	(void)index;
}

void	get_token_semicolumn(char *str, int *index)
{
	(void)str;
	(void)index;
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
	list[QUOTE] = get_token_quote;
	list[DQUOTE] = get_token_dquote;
	list[PIPE] = get_token_pipe;
	list[AMPERSAND] = get_token_ampersant;
	list[SEMICOLUMN] = get_token_semicolumn;
	return (list);
}
