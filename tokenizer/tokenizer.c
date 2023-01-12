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
		// TODO set errno ? / check errno ?
		CRASH("allocation de la liste de pointeur sur fonction fail !!!\n");
		return (ERROR);
	}
	*tokens = NULL;
	*token = NULL;
	*cursor_index = 0;
	return (SUCCESS);
}

t_list *tokenizer(char *cmd) 
/// Renvoie une liste chainee de token (char *) ou NULL en cas d'erreur
/// Prend un string (cmd) non NULL et non modifiable en arg
/// => cmd to tokens
{
	// TODO normer a la fin
	t_list					*tokens;
	char					*token;
	int						cursor_index;
	t_set_token_position	*set_token_position;
	t_position				token_position;


	if (init_tokenizer(&tokens, &token, &cursor_index, &set_token_position) == ERROR)
		return (NULL);  // TODO errno

	while (cursor_index != ft_strlen(cmd))
	{
		set_cursor_after_space(cmd, &cursor_index);
		if (cmd[cursor_index] == '\0')
		{
			// TODO: set errno -> comment ca peut arriver ????
			// si c'est normal -> juste le mettre dans while() et ajouter set_cursor_after_space() a la fin
			break;
		}

		if(set_next_token_position(cmd, cursor_index, set_token_position, &token_position) == ERROR || errno != 0)
		{
			// TODO
			// set errno
			// je ne vois pas d'ou ca pourrais venir, a par des caracteres non imprimables chelou de mechant.
			//ft_lstclear(tokens, free);
			printf(" errno a ete set a %d ", errno); fflush ( stdout );
			perror(":"); fflush ( stdout );
			return (NULL); // + free 
		}
		token = ft_substr(cmd, token_position.start, token_position.end - token_position.start); // FIXME provoque un segfault si token_position.end == 0
		cursor_index = token_position.end;
		if (token != NULL)
		{
			ft_lstadd_back(&tokens, ft_lstnew(token));
			//LOG("added back\n");
		}
		else if (errno != 0)
		{
			// TODO, si on a renvoye NULL et set le errno, erreur quoi
			LOG("NULL renvoye par get_next_token avec errno\n");
			break;
		}
		else
		{
			// TODO ca arrive quand ?
			LOG("NULL renvoye par get_next_token sans errno\n");
			break;
		}
		//set_cursor_after_space(cmd, &cursor_index);
	}
	free(set_token_position);
	printf("|%s|\n", cmd); LOG_TOKENS(tokens); //
	return (tokens);
}
