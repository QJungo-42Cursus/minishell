#include "tokenizer.h"
#include "../tests/debug_helper.h"

#define SPECIAL_CHARACTERS "|&<>()"

static void	set_special_token_position(const char *cmd, int cursor_index, t_position *token_pos)
{
	char	separator;

	separator = cmd[cursor_index];
	token_pos->start = cursor_index;
	while (cmd[cursor_index] != '\0' && cmd[cursor_index] == separator)
		cursor_index++;
	token_pos->end = cursor_index;
}

static void	set_quoted_token_position(const char *cmd, int cursor_index, t_position *token_pos)
{
	char	sep;

	sep = cmd[cursor_index];
	token_pos->start = cursor_index;
	token_pos->end = cursor_index + 1;
	if (cmd[cursor_index + 1] == '\0')
		return ;
	cursor_index++;
	if (cmd[cursor_index] == sep)
		cursor_index++;
	while (cmd[cursor_index] != sep && cmd[cursor_index] != '\0')
		cursor_index++;
	while (!ft_isspace(cmd[cursor_index]) && cmd[cursor_index] != '\0')
		cursor_index++;
	token_pos->end = cursor_index;
}

static void	set_normal_token_position(const char *str, int cursor_index, t_position *token_pos)
{
	t_position	quote_pos;

	token_pos->start = cursor_index;
	while (str[cursor_index] != '\0' && !ft_isspace(str[cursor_index]))
	{
		if (str[cursor_index] == '\'' || str[cursor_index] == '"')
		{
			quote_pos.start = token_pos->start;
			set_quoted_token_position(str, cursor_index, &quote_pos);
			token_pos->end = quote_pos.end;
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

void	set_next_token_position(const char *cmd, int cursor_index, t_position *token_position, t_bool is_expand_mode)
{
	token_position->start = cursor_index;
	if (is_in_charset(cmd[cursor_index], "\"'"))
		set_quoted_token_position(cmd, cursor_index, token_position);
	else if (is_in_charset(cmd[cursor_index], SPECIAL_CHARACTERS) && !is_expand_mode)
		set_special_token_position(cmd, cursor_index, token_position);
	else
		set_normal_token_position(cmd, cursor_index, token_position);
}
