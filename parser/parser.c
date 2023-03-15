/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:45 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/15 11:41:57 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../minishell.h"

extern volatile sig_atomic_t	g_minishell_status;

int	set_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;
	t_list	*cursor;

	if (g_minishell_status == S_HEREDOC_ABORT)
	{
		minishell->last_exit_status = 1;
		cursor = tokens;
		while (cursor != NULL)
		{
			free(cursor->content);
			cursor = cursor->next;
		}
		return (ERROR);
	}
	exit_status = redir(tokens, cmd, minishell);
	if (exit_status == USED || exit_status == ERROR)
		return (exit_status);
	exit_status = pipeline(tokens, cmd, minishell);
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
	{
		free_ast(cmd);
		return (NULL);
	}
	return (cmd);
}
