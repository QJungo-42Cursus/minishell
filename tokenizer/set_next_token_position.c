/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_next_token_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:17:52 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/10 09:27:35 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

#define SPECIAL_CHARACTERS "|&<>"

static void	set_normal_token_position(const char *str,
				int cursor_index, t_position *token_pos, t_bool is_first_call);

static void	set_special_token_position(const char *cmd,
		int cursor_index, t_position *token_pos)
{
	char	separator;

	separator = cmd[cursor_index];
	token_pos->start = cursor_index;
	while (cmd[cursor_index] != '\0' && cmd[cursor_index] == separator)
		cursor_index++;
	token_pos->end = cursor_index;
}

static void	set_quoted_token_position(const char *cmd,
		int cursor_index, t_position *token_pos, t_bool is_first_call)
{
	char	sep;

	sep = cmd[cursor_index];
	if (is_first_call)
		token_pos->start = cursor_index;
	token_pos->end = cursor_index + 1;
	if (cmd[cursor_index + 1] == '\0')
		return ;
	cursor_index++;
	while (cmd[cursor_index] != sep && cmd[cursor_index] != '\0')
		cursor_index++;
	cursor_index++;
	token_pos->end = cursor_index;
	if (is_in_charset(cmd[cursor_index], SPECIAL_CHARACTERS)
		|| ft_isspace(cmd[cursor_index]) || cmd[cursor_index] == '\0')
		return ;
	else if (is_in_charset(cmd[cursor_index], "\"\'"))
		set_quoted_token_position(cmd, cursor_index, token_pos, FALSE);
	else
		set_normal_token_position(cmd, cursor_index, token_pos, FALSE);
}

static void	set_normal_token_position(const char *str,
		int cursor_index, t_position *token_pos, t_bool is_first_call)
{
	if (is_first_call)
		token_pos->start = cursor_index;
	while (str[cursor_index] != '\0' && !ft_isspace(str[cursor_index]))
	{
		if (is_in_charset(str[cursor_index], "\"'"))
		{
			set_quoted_token_position(str, cursor_index, token_pos, FALSE);
			return ;
		}
		if (is_in_charset(str[cursor_index], SPECIAL_CHARACTERS))
		{
			token_pos->end = cursor_index;
			return ;
		}
		cursor_index++;
	}
	token_pos->end = cursor_index;
}

void	set_next_token_position(const char *cmd,
		int cursor_index, t_position *token_position, t_bool is_expand_mode)
{
	token_position->start = cursor_index;
	if (is_in_charset(cmd[cursor_index], "\"'"))
		set_quoted_token_position(cmd, cursor_index, token_position, TRUE);
	else if (is_in_charset(cmd[cursor_index], SPECIAL_CHARACTERS)
		&& !is_expand_mode)
		set_special_token_position(cmd, cursor_index, token_position);
	else
		set_normal_token_position(cmd, cursor_index, token_position, TRUE);
}
