#include "../libft/libft.h"

static int	var_founded(int i, int *start_index,
		int *end_index, const char *token)
{
	*start_index = i;
	i++;
	while (token[i] != '\0' && is_in_charset(token[i], "$:\'\" ") == FALSE)
		i++;
	*end_index = i - 1;
	return (TRUE);
}

int	get_var_position(int begin_from, const char *token,
		int *start_index, int *end_index)
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
			return (var_founded(i, start_index, end_index, token));
		i++;
	}
	return (FALSE);
}
