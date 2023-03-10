/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:45 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/10 09:59:13 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../minishell.h"

int	set_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	int		exit_status;

	exit_status = redir(tokens, cmd, minishell);
	if (exit_status == USED)
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
		return (NULL);
	return (cmd);
}
