/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:01 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/14 17:56:41 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../expansion/expansion.h"

static int	is_token_valid(char *token, t_list *cursor, t_cmd *cmd)
{
	if (get_token_type(token) == HEREDOC)
		return (is_heredoc_valid(cursor->next, cmd));
	return (TRUE);
}

static int	parse(t_list **tokens_cursor,
		t_cmd *cmd, int *i, t_minishell *minishell)
{
	char	*token;
	int		get_heredoc_res;

	token = (char *)(*tokens_cursor)->content;
	if (!is_token_valid(token, *tokens_cursor, cmd))
	{
		free(cmd->s_command.argv);
		return (ERROR);
	}
	get_heredoc_res = get_heredoc(tokens_cursor, cmd);
	if (get_heredoc_res == ERROR)
	{
		free(cmd->s_command.argv);
		malloc_error(minishell);
	}
	if (get_heredoc_res == USED)
		return (SUCCESS);
	cmd->s_command.argv[*i] = (char *)(*tokens_cursor)->content;
	*tokens_cursor = (*tokens_cursor)->next;
	(*i)++;
	return (SUCCESS);
}

static void	expand_all_tokens(t_list **tokens, t_minishell *minishell)
{
	t_list	*cursor;
	t_list	*last;

	last = NULL;
	cursor = *tokens;
	while (cursor != NULL)
	{
		expand((char **)&cursor->content, minishell);
		if (ft_strlen(cursor->content) == 0)
		{
			if (last == NULL)
				*tokens = cursor->next;
			else
				last->next = cursor->next;
			free(cursor->content);
			cursor = cursor->next;
			continue ;
		}
		unquote((char *)cursor->content);
		last = cursor;
		cursor = cursor->next;
	}
}

//#include "../tests/debug_helper.hpp"
//LOG_TOKENS(tokens);

int	parse_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	t_list	*cursor;
	int		i;

	expand_all_tokens(&tokens, minishell);
	if (tokens == NULL)
		return (SUCCESS);
	cmd->type = COMMAND;
	cmd->s_command.argv
		= (char **)malloc(sizeof(char *) * (ft_lstsize(tokens) + 1));
	if (cmd->s_command.argv == NULL)
		malloc_error(minishell);
	cursor = tokens;
	i = 0;
	cmd->s_command.heredoc = NULL;
	while (cursor != NULL)
		if (parse(&cursor, cmd, &i, minishell) == ERROR)
			return (ERROR);
	cmd->s_command.argv[i] = NULL;
	cmd->s_command.next = NULL;
	return (SUCCESS);
}
