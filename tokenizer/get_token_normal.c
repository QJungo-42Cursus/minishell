#include "../libft/libft.h"
#include "tokenizer.h"
#include "stdio.h"

/// Gere si ce n'est entouré par rien
void	get_token_normal(char *str, int *index, int *start, int *end)
{
	//printf("mode normal %s\n", &str[*index]);
	/// Fake start pour pouvoir appeler get_token_(d)quote sans perdre le vrai start
	int		f_start;
	t_sep	sep;

	(*start) = *index;
	while (str[*index] != '\0' && !ft_isspace(str[*index]))
	{
		/// Si on tombe sur un backslash, on skip le backslash pour afficher le char suivant
		if (str[*index] == '\\')
			ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
		if (str[*index] == '"' || str[*index] == '\'')
		{
			/// On va d'abors recuperer le type de separator
			/// Ensuite on va l'ecraser avec le strcpy
			/// puis on va appeler la fonction qui gere le type de separator
			sep = get_sep(str[*index]);
			if (!(sep == DQUOTE || sep == QUOTE))// TODO ce cas ne devrait pas arriver
				exit (66);
			ft_strlcpy(str + *index, str + *index + 1, ft_strlen(str + *index));
			if (sep == DQUOTE)
				get_token_dquote(str, index, &f_start, end);
			else if (sep == QUOTE)
				get_token_quote(str, index, &f_start, end);
			return ;
		}
		/// parse all the redirections (< > >> <<) and pipe (|) here, that are next to the token without spaces
		if (is_in_charset(str[*index], "<>|"))
		{
			(*end) = (*index);
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
