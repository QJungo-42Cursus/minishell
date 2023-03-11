/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:46:42 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/11 14:56:44 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "parser.h"
#include "../minishell.h"
#include "../tests/debug_helper.hpp"

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

static int	skip_redir(int position, t_list *tokens,
						t_minishell *minishell, t_cmd *cmd)
{
	t_list	*cursor;

	if (position == 0)
	{
		free(tokens->content);
		free(tokens->next->content);
		tokens = tokens->next->next;
	}
	else
	{
		cursor = set_cursor(tokens, position - 1);
		free(cursor->next->content);
		free(cursor->next->next->content);
		(cursor->next) = (cursor->next)->next->next;
	}
	if (tokens == NULL)
	{
		cmd->s_redir.cmd = NULL;
		return (USED);
	}
	cmd->s_redir.cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd->s_redir.cmd == NULL)
		malloc_error(minishell);
	set_command(tokens, cmd->s_redir.cmd, minishell);
	return (USED);
}

int	redir(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	t_list	*cursor;
	int		tok_type;
	int		position;
	int		open_res;

	position = get_redir_position(tokens);
	if (position == -2)
	{
		ft_putstr_fd(STR"minishell:"
			" syntax error near unexpected token `newline'\n", 2);
		return (FALSE);
	}
	if (position == NOT_FOUND)
		return (FALSE);
	cursor = set_cursor(tokens, position);
	tok_type = get_token_type((char *)cursor->content);
	cmd->type = (t_cmd_type)tok_type;
	open_res = check_error(cmd, (char *)cursor->next->content);
	if (open_res != ERROR)
		open_res = open_file(cmd, (char *)cursor->next->content);
	if (open_res == ERROR)
		return (ERROR);
	return (skip_redir(position, tokens, minishell, cmd));
}
