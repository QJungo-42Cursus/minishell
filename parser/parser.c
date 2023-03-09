/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:45 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/09 14:33:18 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../minishell.h"
#include "../tests/debug_helper.hpp"

static void	first_logic(t_list **start_right, t_list **cursor)
{
	*start_right = (*cursor)->next->next;
	free((*cursor)->next->content);
	(*cursor)->next = NULL;
}

int	logic(t_list *cursor, t_cmd *cmd, t_minishell *minishell)
{
	int			tok_type;
	t_list		*start_left;
	t_list		*start_right;

	start_left = cursor;
	while (cursor->next != NULL)
	{
		tok_type = get_token_type((char *)cursor->next->content);
		if (tok_type == LOGIC_OR || tok_type == LOGIC_AND)
		{
			first_logic(&start_right, &cursor);
			cmd->type = (t_cmd_type)tok_type;
			cmd->s_logic.left = (t_cmd *)malloc(sizeof(t_cmd));
			if (cmd->s_logic.left == NULL)
				malloc_error(minishell);
			cmd->s_logic.right = (t_cmd *)malloc(sizeof(t_cmd));
			if (cmd->s_logic.right == NULL)
				malloc_error(minishell);
			set_command(start_left, cmd->s_logic.left, minishell);
			set_command(start_right, cmd->s_logic.right, minishell);
			return (USED);
		}
		cursor = cursor->next;
	}
	return (FALSE);
}

int	set_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;

	if (tokens == NULL)
	{
		printf("exit at function : %s()\n", __func__);
		exit(222); ///
		return (FALSE);
	}
	if (are_we_in_parentheses(tokens))
	{
		if (ft_strncmp((char *)tokens->next->content, ")", 2) == 0)
		{
			write(2, "minishell: syntax error near unexpected token `)'\n", 50);
			return (ERROR);
		}
		tokens = lst_cut_first_and_last(tokens);
	}
	exit_status = logic(tokens, cmd, minishell);
	if (exit_status == USED)
		return (exit_status);
	exit_status = pipeline(tokens, cmd, minishell);
	if (exit_status == USED)
		return (exit_status);
	exit_status = redir(tokens, cmd, minishell);
	if (exit_status == USED)
		return (exit_status);
	exit_status = parse_command(tokens, cmd, minishell);
	return (exit_status);
}

t_cmd	*parser(t_list *tokens, t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		malloc_error(minishell);
	if (set_command(tokens, cmd, minishell) == ERROR)
		return (NULL);
	return (cmd);
}
