#include "tokenizer.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


/// Renvoie un substr du prochain token qu'il se charge de trouver + avance le curseur (l'index)
/// En cas d'erreur, renvoie NULL ET set errno
/// Il peut arriver qu'il renvoie NULL sans erreur (ex: ' echo salut ""')
///    -> Dans ce cas, il faut juste passer au token suivant
char	*get_next_token(char *str, int *index)
{
	//char		*token;
	int			start;
	int			end;
	t_sep		sep;
	t_get_token	*get_token;

	/// Check if the string is empty
	if (str[*index] == '\0' || str == NULL || index == NULL)
	{
		// TODO: set errno
		return (NULL);
	}

	/// cut the space before the tokens
	while (ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;

	/// Set le debut du token a l'index courant de la chaine
	start = *index;
	
	/// agit en fonction du 1er char, qui fera office de separateur, s'il rentre dans l'enum t_sep
	sep = get_sep(str[*index]);
	if (sep == SEP_ERROR)
	{
		// TODO
		// set errno
		// je ne vois pas d'ou ca pourrais venir, a par des caracteres non imprimables chelou de mechant.
		printf("SEP_ERROR\n");
		return (NULL);
	}
	else
	{
		get_token = list_func();
		if (get_token == NULL)
		{
			// TODO
			// set errno ? / check errno ?
			return (NULL);
		}
		get_token[sep](str, index, &start, &end); // TODO rename get_token to set_indexes
		free(get_token); // TODO ne pas l'allouer a chaque fois ?? 
	}
	if (start == -1 || end == start)
		return (NULL);
	else
		return(ft_substr(str, start, end - start));
}

void	tokenize(char *line, int *index, t_list **tokens)
{
	char	*token;

	token = get_next_token(line, index);
	if (errno != 0)
	{
		printf(" errno a ete set a %d !!! \n", errno);
		perror(":");
		// TODO
		// set errno
		// je ne vois pas d'ou ca pourrais venir, a par des caracteres non imprimables chelou de mechant.
		//ft_lstclear(tokens, free);
		//return ;
	}
	if (token != NULL)
	{
		ft_lstadd_back(tokens, ft_lstnew(token));
		printf("added back\n");
	}
	else if (errno != 0)
	{
		printf("NULL renvoye par get_next_token avec errno\n");
		// TODO, si on a renvoye NULL et set le errno, erreur quoi
	}
	else
		printf("NULL renvoye par get_next_token sans errno\n");
	if (*index == ft_strlen(line))
		return ;
	tokenize(line, index, tokens);
}

t_list *tokenizer(char *str)
{
	t_list	*tokens;
	int		index;
	char	*trimed_str;

	trimed_str = ft_strtrim(str, " \r\t\v\f\n"); // TODO le \n c'est va marcher??
	index = 0;
	tokens = NULL;
	tokenize(trimed_str, &index, &tokens);
	return (tokens);
}
