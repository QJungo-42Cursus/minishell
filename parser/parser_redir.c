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
	while (cursor->next != NULL)
	{
		tok_type = get_token_type((char *)cursor->content);
		LOG_SEP(tok_type);
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
	if (cursor->next == NULL)
		return (-2);
	return (NOT_FOUND);
}

int	redir(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	t_list	*cursor;
	int		tok_type;
	int		position;

	printf("redir tokens :");//
	LOG_TOKENS(tokens);

	position = get_redir_position(tokens);
	if (position == -2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
		return (FALSE); // TODO crash, can't get next token
	}
	if (position == NOT_FOUND)
		return (FALSE);

	cursor = tokens;
	while (cursor->next != NULL)
	{
		tok_type = get_token_type((char *)cursor->next->content);
		if (tok_type == REDIR_IN
			|| tok_type == REDIR_OUT
			|| tok_type == REDIR_APPEND)
		{
			cmd->type = (t_cmd_type)tok_type;
			cmd->s_redir.filename = (char *)cursor->next->next->content;
			// TODO direct ouvrir le fichier je crois

			cursor->next = cursor->next->next->next;

			cmd->s_redir.cmd = (t_cmd *)malloc(sizeof(t_cmd));
			if (cmd->s_redir.cmd == NULL)
				malloc_error(minishell);
			set_command(tokens, cmd->s_redir.cmd, minishell);
			return (USED);
		}
		cursor = cursor->next;
	}
	return (FALSE);
}

