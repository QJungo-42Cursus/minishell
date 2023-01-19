#include "tokenizer.h"
#include "../tests/debug_helper.h"

int	set_next_token_position(const char *cmd, int cursor_index, t_set_token_position *set_token_position, t_position *token_position)
{
	t_sep	separator;

	token_position->start = cursor_index;
	separator = get_sep(cmd[cursor_index]);
	set_token_position[separator](cmd, cursor_index, token_position);
	return (SUCCESS);
}
