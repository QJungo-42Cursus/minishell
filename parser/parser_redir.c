#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../minishell.h"
#include "../tests/debug_helper.hpp"

/*
int	first_token_redir(t_list **tokens, t_cmd *cmd, t_minishell *minishell)
{
	t_list		*cursor;
	int			tok_type;

	cursor = *tokens;
	tok_type = get_token_type((char *)cursor->content);
	if (tok_type == REDIR_IN || tok_type == REDIR_OUT
		|| tok_type == REDIR_APPEND)
	{
		cmd->type = (t_cmd_type)tok_type;
		cmd->s_redir.filename = (char *)cursor->next->content;
		cmd->s_redir.cmd = (t_cmd *)malloc(sizeof(t_cmd));
		if (cmd->s_redir.cmd == NULL)
			malloc_error(minishell);
		set_command((*tokens)->next->next, cmd->s_redir.cmd, minishell);
		return (USED);
	}
	return (FALSE);
}
*/

#define NOT_FOUND -1

static int	get_redir_position(t_list *tokens)
{
	t_list	*cursor;
	int		tok_type;
	int		position;

	cursor = tokens;
	position = 0;
	while (cursor != NULL)
	{
		tok_type = get_token_type((char *)cursor->content);
		if (tok_type == REDIR_IN || tok_type == REDIR_OUT
			|| tok_type == REDIR_APPEND)
		{
			if (cursor->next == NULL)
				return (-2);
			return (position);
		}
		position++;
		cursor = cursor->next;
	}
	return (NOT_FOUND);
}

static t_list	*set_cursor(t_list *tokens, int position)
{
	t_list	*cursor;
	int		i;

	cursor = tokens;
	i = 0;
	while (i < position)
	{
		if (cursor->next == NULL)
			return (cursor);
		cursor = cursor->next;
		i++;
	}
	return (cursor);
}

int	redir(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	t_list	*cursor;
	int		tok_type;
	int		position;

	position = get_redir_position(tokens);
	printf("get_redir_position returned: %d\n", position);
	if (position == -2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (FALSE); // TODO crash, can't get next token
	}
	if (position == NOT_FOUND)
		return (FALSE);
	cursor = set_cursor(tokens, position);

	tok_type = get_token_type((char *)cursor->content);
	cmd->type = (t_cmd_type)tok_type;
	cmd->s_redir.filename = (char *)cursor->next->content;
	// TODO direct ouvrir le fichier je crois

	if (position == 0)
		tokens = tokens->next->next;
	else
	{
		cursor = set_cursor(tokens, position - 1);
		cursor->next = cursor->next->next->next;
	}
	if (tokens == NULL)
	{
		// TODO, pas de suite ?
		// juste il ouvre le fichier et tchao !
	}
	cmd->s_redir.cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd->s_redir.cmd == NULL)
		malloc_error(minishell);
	set_command(tokens, cmd->s_redir.cmd, minishell);
	return (USED);
}

