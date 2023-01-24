#include <stdio.h>
#include "parser.h"
#include "../libft/libft.h"

int get_token_type(char *token)
{
	if (ft_strncmp(token, "(", 2) == 0)
		return OPEN_PARENTHESES;
	else if (ft_strncmp(token, ")", 2) == 0)
		return CLOSE_PARENTHESES;
	else if (ft_strncmp(token, "&&", 3) == 0)
		return LOGIC_AND;
	else if (ft_strncmp(token, "||", 3) == 0)
		return LOGIC_OR;
	else if (ft_strncmp(token, "|", 2) == 0)
		return PIPELINE;
	else if (ft_strncmp(token, ">>", 3) == 0)
		return REDIR_APPEND;
	else if (ft_strncmp(token, "<", 2) == 0)
		return REDIR_IN;
	else if (ft_strncmp(token, ">", 2) == 0)
		return REDIR_OUT;
	else
		return COMMAND;
}

t_bool	are_we_in_parentheses(t_list *tokens)
{
	t_list		*cursor;
	int			parentheses;

	if (get_token_type((char *)tokens->content) != OPEN_PARENTHESES)
		return (FALSE);
	cursor = tokens;
	parentheses = 0;
	while (cursor != NULL)
	{
		if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
			parentheses++;
		else if (get_token_type((char *)cursor->content) == CLOSE_PARENTHESES)
			parentheses--;
		if (parentheses == 0 && cursor->next == NULL)
			return (TRUE);
		cursor = cursor->next;
	}
	return (FALSE);
}

/* renvoie un pointeur sur le token ")" fermant le 1er groupe de parentheses 
 * si pas de parentheses des le debut, renvoie le meme pointeur
 */
t_list	*skip_parentheses(t_list *cursor)
{
	int			parentheses;

	parentheses = 0;
	if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
	{
		parentheses++;
		while (parentheses > 0)
		{
			cursor = cursor->next;
			if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
				parentheses++;
			else if (get_token_type((char *)cursor->content) == CLOSE_PARENTHESES)
				parentheses--;
		}
	}
	return (cursor);
}

t_list	*lst_cut_first_and_last(t_list *tokens)
{
	t_list		*cursor;
	//t_list		*tmp;

	/* une sorte de "trim", ca enleve le debut et la fin de la t_list */
	cursor = tokens;
	while (cursor->next->next != NULL)
		cursor = cursor->next;
	cursor->next = NULL;
	cursor = tokens->next;
	return (cursor);
}
