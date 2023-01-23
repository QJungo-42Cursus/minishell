#include "../libft/libft.h"

int	get_var_position(int begin_from, const char *token, int *start_index, int *end_index)
{
	int		quoted;
	int		i;

	quoted = FALSE;
	i = begin_from;
	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			quoted = !quoted;
		if (token[i] == '$' && !quoted)
		{
			*start_index = i;
			i++;
			// TODO voire tout les separateurs
			while (token[i] != '\0' && is_in_charset(token[i], "$:\'\" ") == FALSE)
				i++;
			*end_index = i - 1;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
