#include "tokenizer.h"
#include "../libft/libft.h"
#include <stdio.h>

/*
 * TODO
 * ajouter un flag pour savoir si on est dans une quote ou une dquote
 * -> comme ca on peut savoir si l'ats va prendre en compte les $
 */
void	get_token_dquote(char *str, int *index, int *start, int *end);
void	get_token_quote(char *str, int *index, int *start, int *end);


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
	/// Fake start pour pouvoir appeler get_token_(d)quote sans perdre le vrai start
	int		f_start;

	(*start) = *index;
	while (str[*index] != '\0' && !ft_isspace(str[*index]))
	{
		/// Si on tombe sur un backslash, on skip le backslash pour afficher le char suivant
		if (str[*index] == '\\')
			ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
		if (str[*index] == '"' || str[*index] == '\'')
		{
			ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
			if (str[*index] == '"')
				get_token_dquote(str, index, &f_start, end);
			else
				get_token_quote(str, index, &f_start, end);
			return ;
		}
		(*index)++;
	}
	(*end) = (*index);

	/*
	 * Inutile pour le normal ? TODO
	if (!ft_isspace(str[*index]) && str[*index] != '\0')
		ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
	while (!ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;
	*/
}

/// Gere les double quotes "
void	get_token_dquote(char *str, int *index, int *start, int *end)
{
	/// Si c'est le dernier char -> error
	/// Vu que j'ai trim au debut, pas besoin de chercher apres
	if (str[*index + 1] == '\0')
	{
		// TODO
		// printf("ERROR: DQUOTE not closed\n");
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
		/*
		printf("DQUOTE empty\n");
		if (str[*index] == '\0')
			printf("DQUOTE empty and end of line\n");
			*/
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

	/// S'il reste du texte apres le quote, on le lit jusqu'a un isspace
	if (!ft_isspace(str[*index]) && str[*index] != '\0')
		ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
	while (!ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;

	(*end) = (*index);
}

/// Gere les simples quotes '
void	get_token_quote(char *str, int *index, int *start, int *end)
{
	/// Si c'est le dernier char -> error
	/// Vu que j'ai trim au debut, pas besoin de chercher apres
	if (str[*index + 1] == '\0')
	{
		// TODO
		printf("ERROR: QUOTE not closed\n");
		exit (1);
		return ;
	}

	/// Si les quotes sont fermées et vide, on cherche la suite
	(*index)++;
	if (str[*index] == '\'')
	{
		(*start) = *index + 1;
		while (!ft_isspace(str[*index]) && str[*index] != '\0')
			(*index)++;
		(*end) = *index;
		printf("QUOTE empty\n");
		if (str[*index] == '\0')
			printf("QUOTE empty and end of line\n");
		return ;
	}

	/// Sinon mode dquote "normal"
	(*start) = *index;
	while (str[*index] != '\0' && str[*index] != '\'')
		(*index)++;

	/// S'il reste du texte apres le quote, on le lit jusqu'a un isspace
	if (!ft_isspace(str[*index]) && str[*index] != '\0')
		ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
	while (!ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;

	(*end) = (*index);
}

/*
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
	list[QUOTE] = get_token_quote;
	//list[PIPE] = get_token_pipe;
	//list[AMPERSAND] = get_token_ampersant;
	//list[SEMICOLUMN] = get_token_semicolumn;
	return (list);
}
