#include <stdlib.h>
#include <stdio.h>
#include "../libft/libft.h"

/// Gere les double quotes "
void	get_token_dquote(char *str, int *index, int *start, int *end)
{
	printf("dquote %s \n", &str[*index]);

	/// Si c'est le dernier char -> error
	/// Vu que j'ai trim au debut, pas besoin de chercher apres
	if (str[*index + 1] == '\0')
	{
		*start = 0;
		*end = 0;
		// TODO
		printf("ERROR: DQUOTE not closed\n");
		//exit (1);
		return ;
	}

	/// Si les dquotes sont fermées et vide, on cherche la suite
	(*index)++;
	if (str[*index] == '"')
	{

		// test: juste ou passe au prochain token
		*start = 0;
		*end = 0;
		(*index)++;
		return ;



		// mode ou on cherche comme avant :
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
