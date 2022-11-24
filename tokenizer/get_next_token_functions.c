#include "tokenizer.h"
#include "../libft/libft.h"
#include <stdio.h>

void	get_token_dquote(char *str, int *index, int *start, int *end);

void	log_sep(t_sep sep)
{
	if (sep == AMPERSAND)
		printf("AMPERSAND");
	else if (sep == PIPE)
		printf("PIPE");
	else if (sep == SEMICOLUMN)
		printf("SEMICOLON");
	else if (sep == LESS)
		printf("LESS");
	else if (sep == GREATER)
		printf("GREAT");
	else if (sep == QUOTE)
		printf("QUOTE");
	else if (sep == DQUOTE)
		printf("DQUOTE");
	else if (sep == BACKSLASH)
		printf("BACKSLASH");
	else if (sep == NONE)
		printf("NONE");
	else if (sep == SEP_ERROR)
		printf("ERROR");
	else
		printf("UNKNOWN");
	printf(" (%d)\n", sep);

}

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
	return (-1);
}

/// Gere si ce n'est entouré par rien
void	get_token_normal(char *str, int *index, int *start, int *end)
{
	/// Fake start and end pour pouvoir appeler get_token_(d)quote sans perdre le vrai start
	int		f_start;
	int		f_end;

	printf("get_token_normal\n");
	(*start) = *index;
	while (str[*index] != '\0' && !ft_isspace(str[*index]))
	{
		/// Si on tombe sur un backslash, on skip le backslash pour afficher le char suivant
		if (str[*index] == '\\')
			ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
		if (str[*index] == '"')
		{
			printf("DQUOTE in normal\n");
			get_token_dquote(str, index, &f_start, &f_end);
			*end = f_end;
		}
		/*
		else if (str[*index] == '\'')
		{
			(*index)++;
			get_token_quote(str, index, &f_start, &f_end);
			(*index)++;
		}
		*/
		else
			(*index)++;

		(*index)++;
	}




	if (!ft_isspace(str[*index]) && str[*index] != '\0')
		ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
	while (!ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;
	(*end) = (*index);
}

/// Gere les double quotes "
void	get_token_dquote(char *str, int *index, int *start, int *end)
{
	/// Si c'est le dernier char -> error
	/// Vu que j'ai trim au debut, pas besoin de chercher apres
	if (str[*index + 1] == '\0')
	{
		// TODO
		printf("ERROR: DQUOTE not closed\n");
		exit (1);
		return ;
	}

	/// Si les dquotes sont fermées et vide, on cherche la suite
	(*index)++;
	if (str[*index] == '"')
	{
		(*start) = *index + 1;
		while (!ft_isspace(str[*index]) && str[*index] != '\0')
			(*index)++;
		(*end) = *index;
		printf("DQUOTE empty\n");
		if (str[*index] == '\0')
			printf("DQUOTE empty and end of line\n");
		return ;
	}

	/// Sinon mode dquote "normal"
	(*start) = *index;
	while (str[*index] != '\0' && str[*index] != '"')
	{
		/// Si on tombe sur un backslash, on skip le backslash pour afficher le char suivant
		if (str[*index] == '\\')
			ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
		(*index)++;
	}
	if (!ft_isspace(str[*index]) && str[*index] != '\0')
		ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
	while (!ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;
	(*end) = (*index);
}

/*
void	get_token_quote(char *str, int *index, int *start)
{
	(*index)++;
	if (str[*index] == '\'')
		return ;
	while (str[*index] != '\0' && str[*index] != '\'')
		(*index)++;
	(void)start; // TODO
}

void	get_token_pipe(char *str, int *index, int *start) // TODO autre term tech ?
{
	(void)str;
	(void)index;
}

void	get_token_ampersant(char *str, int *index, int *start) // TODO ortho
{
	(void)str;
	(void)index;
}

void	get_token_semicolumn(char *str, int *index, int *start)
{
	(void)str;
	(void)index;
}

*/
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

	//list[QUOTE] = get_token_quote;
	//list[PIPE] = get_token_pipe;
	//list[AMPERSAND] = get_token_ampersant;
	//list[SEMICOLUMN] = get_token_semicolumn;
	return (list);
}
