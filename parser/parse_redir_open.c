/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_open.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:34:27 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/11 19:36:14 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int	open_file(t_cmd *cmd, char *filename)
{
	if (cmd->type == REDIR_APPEND)
		cmd->s_redir.fd = open(filename,
				O_APPEND | O_CREAT | O_RDWR, 0000644);
	else if (cmd->type == REDIR_OUT)
		cmd->s_redir.fd = open(filename,
				O_TRUNC | O_CREAT | O_RDWR, 0000644);
	else if (cmd->type == REDIR_IN)
		cmd->s_redir.fd = open(filename, O_RDONLY);
	if (cmd->s_redir.fd == -1)
	{
		perror(STR"minishell: open");
		return (ERROR);
	}
	return (SUCCESS);
}

int	check_error(t_cmd *cmd, char *filename)
{
	if (cmd->type == REDIR_IN && access(filename, F_OK) != 0)
	{
		ft_putstr_fd(STR"minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(STR": No such file or directory\n", 2);
		return (ERROR);
	}
	if ((cmd->type == REDIR_APPEND || cmd->type == REDIR_OUT)
		&& access(filename, F_OK) != 0)
		return (SUCCESS);
	if (((cmd->type == REDIR_APPEND || cmd->type == REDIR_OUT)
			&& access(filename, W_OK) != 0)
		|| (cmd->type == REDIR_IN && access(filename, R_OK) != 0))
	{
		ft_putstr_fd(STR"minishell: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(STR": Permission denied\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}
