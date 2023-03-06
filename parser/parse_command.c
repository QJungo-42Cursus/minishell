/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:01 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/06 10:31:21 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../expansion/expansion.h"

static int	is_token_valid(char *token, t_list *cursor, t_cmd *cmd)
{
	if (get_token_type(token) == OPEN_PARENTHESES)
	{
		write(STDERR_FILENO, UNEXPECTED_TOKEN, 47);
		if (cursor->next == NULL)
			write(STDERR_FILENO, "newline", 7);
		else
			write(STDERR_FILENO, (char *)cursor->next->content,
				ft_strlen((char *)cursor->next->content));
		write(STDERR_FILENO, "'\n", 2);
		return (FALSE);
	}
	if (get_token_type(token) == CLOSE_PARENTHESES)
	{
		write(STDERR_FILENO, UNEXPECTED_TOKEN, 47);
		write(STDERR_FILENO, token, ft_strlen(token));
		write(STDERR_FILENO, "'\n", 2);
		return (FALSE);
	}
	if (get_token_type(token) == HEREDOC)
		return (is_heredoc_valid(cursor->next, cmd));
	return (TRUE);
}

// malloc OK !
static int	unquote_and_expand(t_list **tokens,
		t_cmd *cmd, t_minishell *minishell)
{
	*tokens = expand_and_retokenize(*tokens, minishell);
	cmd->type = COMMAND;
	cmd->s_command.argv
		= (char **)malloc(sizeof(char *) * (ft_lstsize(*tokens) + 1));
	if (cmd->s_command.argv == NULL)
		malloc_error(minishell);
	return (SUCCESS);
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

int	parse_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	t_list	*cursor;
	int		i;

	unquote_and_expand(&tokens, cmd, minishell);
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
