/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:57 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/15 12:09:08 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include "../minishell.h"
#include <unistd.h>

extern volatile sig_atomic_t	g_minishell_status;

int	is_heredoc_valid(t_list *cursor, t_cmd *cmd)
{
	char	*token;

	(void)cmd;
	if (cursor == NULL)
	{
		write(STDERR_FILENO, UNEXPECTED_TOKEN"newline'\n", 55);
		return (FALSE);
	}
	token = (char *)cursor->content;
	if (get_token_type(token) != COMMAND)
	{
		write(STDERR_FILENO, UNEXPECTED_TOKEN, 47);
		write(STDERR_FILENO, token, ft_strlen(token));
		write(STDERR_FILENO, "'\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	is_delimiter(char *line, char *delimiter)
{
	int		delimiter_len;

	delimiter_len = ft_strlen(delimiter);
	return ((t_bool)(ft_strncmp(line, delimiter, delimiter_len) == 0
		&& line[delimiter_len] == '\n'
		&& ft_strlen(line) == delimiter_len + 1));
}

static t_bool	stop(char *line, char *delimiter)
{
	if (g_minishell_status == S_HEREDOC_ABORT)
		return (TRUE);
	if (line == NULL)
	{
		ft_putstr_fd("\nminishell: warning: here-document delimited by "
			"end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
		return (TRUE);
	}
	if (is_delimiter(line, delimiter))
	{
		free(line);
		return (TRUE);
	}
	return (FALSE);
}

static char	*get_heredoc_input(char *delimiter)
{
	char	*line;
	char	*input;
	char	*to_free;

	input = ft_strdup((char *)"");
	if (input == NULL)
		return (NULL);
	while (TRUE)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (stop(line, delimiter))
			break ;
		to_free = input;
		input = ft_strjoin(input, line);
		free(to_free);
		free(line);
	}
	return (input);
}

int	get_heredoc(t_list **token_cursor, t_cmd *cmd)
{
	if (ft_strncmp((char *)(*token_cursor)->content, "<<", 3) != 0)
		return (SUCCESS);
	g_minishell_status = S_HEREDOC;
	cmd->s_command.heredoc
		= get_heredoc_input((char *)(*token_cursor)->next->content);
	free((*token_cursor)->content);
	free((*token_cursor)->next->content);
	if (cmd->s_command.heredoc == NULL)
		return (ERROR);
	if (g_minishell_status == S_HEREDOC_ABORT)
	{
		free(cmd->s_command.heredoc);
		cmd->s_command.heredoc = NULL;
	}
	*token_cursor = (*token_cursor)->next->next;
	return (USED);
}
