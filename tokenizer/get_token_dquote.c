#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

/// Gere les double quotes "
void	get_token_dquote(char *str, int *index, int *start, int *end)
{
	/// Si c'est le dernier char -> error
	/// Vu que j'ai trim au debut, pas besoin de chercher apres
	if (str[*index + 1] == '\0')
	{
		*start = -1;
		*end = -1;
		printf("TODO: DQUOTE not closed\n");
		return ;
	}

	/// Si les dquotes sont fermées et vide on renvoie un token vide
	(*index)++;
	if (str[*index] == '"')
	{
		*end = -1;
		*start = -1; // TODO c'est pas fait expres, mais quand je le met a 0, ca marche pas, le -1 marche
		(*index)++;
		return ;
	}

	/// Sinon mode dquote "normal"
	(*start) = *index;
	while (str[*index] != '"')
	{
		/// Si on tombe sur un backslash, on skip le backslash pour afficher le char suivant
		/// Si c'etait un dquote, il va automatiquement le skip, apres le ft_strlcpy et le index++
		if (str[*index] == '\\')
			ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
		if (str[*index] == '\0')
		{
			// TODO s'il tombe sur le \0 avant le dqoute fermant, lire la prochaine ligne (comportement bash)
			printf("TODO: DQUOTE not closed\n");
			break ;
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
