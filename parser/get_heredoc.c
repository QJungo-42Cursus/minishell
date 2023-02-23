/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:57 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:39:29 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../libft/libft.h"
#include "../expansion/expansion.h"
#include "../tokenizer/tokenizer.h"
#include "../expansion/expansion.h"

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

static char	*get_heredoc_input(char *delimiter)
{
	char	*line;
	char	*input;
	char	*to_free;

	input = ft_strdup((char *)"");
	while (TRUE)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			return (NULL);
		if (is_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		to_free = input;
		input = ft_strjoin(input, line);
		free(to_free);
		free(line);
	}
	return (input);
}

int	get_heredoc(t_list **cursor, t_cmd *cmd)
{
	if (ft_strncmp((char *)(*cursor)->content, "<<", 3) != 0)
		return (SUCCESS);
	cmd->s_command.heredoc
		= get_heredoc_input((char *)(*cursor)->next->content);
	if (cmd->s_command.heredoc == NULL)
		return (ERROR);
	*cursor = (*cursor)->next->next;
	return (USED);
}
