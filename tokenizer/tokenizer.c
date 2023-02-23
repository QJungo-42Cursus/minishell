#include "tokenizer.h"
#include "../libft/libft.h"
#include "../tests/debug_helper.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static void	set_cursor_after_space(const char *cmd, int *cursor_index)
{
	while (ft_isspace(cmd[*cursor_index]) && cmd[*cursor_index] != '\0')
		(*cursor_index)++;
}

/// Renvoie une liste chainee de token (char *) ou NULL en cas d'erreur
/// TODO Voir chaine vide. 
/// Prend un string (cmd) non NULL et non modifiable en arg
/// => cmd to tokens
t_list	*tokenizer(const char *cmd, t_bool is_expand_mode)
{
	t_list					*tokens;
	char					*token;
	int						cursor_index;
	t_position				token_position;

	tokens = NULL;
	token = NULL;
	cursor_index = 0;
	set_cursor_after_space(cmd, &cursor_index);
	while (cmd[cursor_index] != '\0')
	{
		set_next_token_position(cmd, cursor_index,
			&token_position, is_expand_mode);
		token = ft_substr(cmd, token_position.start,
				token_position.end - token_position.start);
		if (token == NULL)
		{
			ft_lstclear(&tokens, free);
			return (NULL);
		}
		ft_lstadd_back(&tokens, ft_lstnew(token));
		cursor_index = token_position.end;
		set_cursor_after_space(cmd, &cursor_index);
	}
	return (tokens);
}
