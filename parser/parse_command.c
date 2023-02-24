/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:01 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:03:20 by qjungo           ###   ########.fr       */
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

static int	unquote_and_expand(t_list **tokens,
		t_cmd *cmd, t_minishell *minishell)
{
	t_list	*cursor;

	*tokens = expand_and_retokenize(*tokens, minishell);
	cursor = *tokens;
	while (cursor != NULL)
	{
		unquote((char *)cursor->content);
		cursor = cursor->next;
	}
	cmd->type = COMMAND;
	cmd->s_command.argv
		= (char **)malloc(sizeof(char *) * (ft_lstsize(*tokens) + 1));
	return (SUCCESS);
}

static int	parse(t_list **cursor, t_cmd *cmd, int *i)
{
	char	*token;
	int		get_heredoc_res;

	token = (char *)(*cursor)->content;
	if (!is_token_valid(token, *cursor, cmd))
	{
		free(cmd->s_command.argv);
		return (ERROR);
	}
	get_heredoc_res = get_heredoc(cursor, cmd);
	if (get_heredoc_res == ERROR)
	{
		// TODO
		free(cmd->s_command.argv);
		return (ERROR);
	}
	if (get_heredoc_res == USED)
		return (SUCCESS);
	cmd->s_command.argv[*i] = (char *)(*cursor)->content;
	*cursor = (*cursor)->next;
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
	while (cursor != NULL)
		if (parse(&cursor, cmd, &i) == ERROR)
			return (ERROR);
	cmd->s_command.argv[i] = NULL;
	cmd->s_command.next = NULL;
	cmd->s_command.heredoc = NULL;
	return (SUCCESS);
}
