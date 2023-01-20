#include "tokenizer.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../tests/debug_helper.h"

static void	set_cursor_after_space(const char *const cmd, int *const cursor_index)
{
	while (ft_isspace(cmd[*cursor_index]) && cmd[*cursor_index] != '\0')
		(*cursor_index)++;
}

static int	init_tokenizer(t_list **tokens, char **token, int *cursor_index, t_set_token_position **set_token_position)
{
	*set_token_position = list_func();
	if (*set_token_position == NULL)
	{
		CRASH("allocation de la liste de pointeur sur fonction fail !!!\n");
		return (ERROR);
	}
	*tokens = NULL;
	*token = NULL;
	*cursor_index = 0;
	return (SUCCESS);
}

t_list *tokenizer(const char *cmd) 
/// Renvoie une liste chainee de token (char *) ou NULL en cas d'erreur
/// TODO Voir chaine vide. 
/// Prend un string (cmd) non NULL et non modifiable en arg
/// => cmd to tokens
{
	t_list					*tokens;
	char					*token;
	int						cursor_index;
	t_set_token_position	*set_token_position;
	t_position				token_position;

	if (init_tokenizer(&tokens, &token, &cursor_index, &set_token_position) == ERROR)
		return (NULL); 
	while (cursor_index != ft_strlen(cmd))
	{
		set_cursor_after_space(cmd, &cursor_index);
		if (cmd[cursor_index] == '\0')
		{
			errno = EINVAL;
			break;
		}
		if (set_next_token_position(cmd, cursor_index, set_token_position, &token_position) == ERROR)
		{
			// TODO
			//ft_lstclear(tokens, free);
			printf(" errno a ete set a %d ", errno); fflush ( stdout );
			perror(":"); fflush ( stdout );
			return (NULL); // + free 
		}
		// TODO -> check si c'est dquote / quote vide (ex '' / "") et skip
		token = ft_substr(cmd, token_position.start, token_position.end - token_position.start); // FIXME provoque un segfault si token_position.end == 0
		if (token == NULL)
		{
			// TODO free list ..
			free(set_token_position);
		}
		ft_lstadd_back(&tokens, ft_lstnew(token));
		cursor_index = token_position.end;
	}
	free(set_token_position);
	return (tokens);
}
