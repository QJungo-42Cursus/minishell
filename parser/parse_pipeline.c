/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:04 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/10 09:45:21 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include "../builtins/builtins.h"

int	number_of_pipe_operator(t_list *cursor)
{
	int		size;

	size = 0;
	while (cursor != NULL)
	{
		if (get_token_type((char *)cursor->content) == PIPELINE)
			size++;
		cursor = cursor->next;
	}
	return (size);
}

t_list	*set_pipeline_to_null_and_return_next(t_list *cursor)
{
	t_list		*next_node_is_null;

	while (cursor->next != NULL)
	{
		if (get_token_type((char *)cursor->next->content) == PIPELINE)
		{
			next_node_is_null = cursor;
			cursor = cursor->next->next;
			free(next_node_is_null->next->content);
			next_node_is_null->next = NULL;
			return (cursor);
		}
		cursor = cursor->next;
	}
	return (NULL);
}

static void	end(t_cmd **cmd_cursor, t_minishell *minishell, t_list *start)
{
	(*cmd_cursor)->s_command.next = (t_cmd *)malloc(sizeof(t_cmd));
	if ((*cmd_cursor)->s_command.next == NULL)
		malloc_error(minishell);
	set_command(start, (*cmd_cursor)->s_command.next, minishell);
}

// malloc OK !
static void	set_pipeline_and_args(t_list *cursor,
	t_cmd *cmd, t_minishell *minishell)
{
	t_list		*start;
	t_cmd		*new_cmd;
	t_cmd		*cmd_cursor;

	start = cursor;
	cmd_cursor = cmd;
	while (TRUE)
	{
		cursor = set_pipeline_to_null_and_return_next(cursor);
		if (cursor == NULL)
			break ;
		new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
		if (new_cmd == NULL)
			malloc_error(minishell);
		set_command(start, new_cmd, minishell);
		if (cmd_cursor->type == PIPELINE)
			cmd_cursor->s_pipeline.first_cmd = new_cmd;
		else
			cmd_cursor->s_command.next = new_cmd;
		cmd_cursor = new_cmd;
		start = cursor;
	}
	end(&cmd_cursor, minishell, start);
}

int	pipeline(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	cmd->s_pipeline.pipe_count = number_of_pipe_operator(tokens);
	if (cmd->s_pipeline.pipe_count == 0)
		return (FALSE);
	cmd->s_pipeline.pipe_count++;
	cmd->type = PIPELINE;
	set_pipeline_and_args(tokens, cmd, minishell);
	return (USED);
}
