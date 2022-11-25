#include <stdio.h>
#include "../libft/libft.h"

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
