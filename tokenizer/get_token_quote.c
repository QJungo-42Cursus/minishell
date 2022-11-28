#include <stdio.h>
#include "../libft/libft.h"

/// Gere les simples quotes '
void	get_token_quote(char *str, int *index, int *start, int *end)
{
	//printf("quote %s \n", &str[*index]);
	/// Si c'est le dernier char -> error
	/// Vu que j'ai trim au debut, pas besoin de chercher apres
	if (str[*index + 1] == '\0')
	{
		// TODO
		printf("TODO: QUOTE not closed\n");
		*end = *index;
		return ;
	}

	/// Si les quotes sont fermées et vide, on cherche la suite
	(*index)++;
	if (str[*index] == '\'')
	{
		*end = -1;
		*start = -1; // TODO c'est pas fait expres, mais quand je le met a 0, ca marche pas
		(*index)++;
		return ;
	}

	/// Sinon mode dquote "normal"
	(*start) = *index;
	while (str[*index] != '\'')
	{
		if (str[*index] == '\0')
		{
			// TODO
			printf("TODO: QUOTE not closed\n");
			*end = *index;
			return ;
		}
		(*index)++;
	}

	/// S'il reste du texte apres le quote, on le lit jusqu'a un isspace
	if (!ft_isspace(str[*index]) && str[*index] != '\0')
		ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
	while (!ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;
	(*end) = (*index);
}
