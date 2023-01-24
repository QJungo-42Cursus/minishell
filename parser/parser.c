#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../libft/libft.h"

t_bool	logic(t_list *cursor, t_cmd *cmd)
{
	int			tok_type;
	t_list		*start_left = cursor;
	t_list		*start_right = cursor;

	while (cursor->next != NULL)
	{
		cursor = skip_parentheses(cursor);

		tok_type = get_token_type((char *)cursor->next->content);
		if (tok_type == LOGIC_OR || tok_type == LOGIC_AND)
		{
			start_right = cursor->next->next;
			free(cursor->next->content);
			cursor->next = NULL;

			cmd->type = (t_cmd_type)tok_type;
			cmd->logic.left = (t_cmd *)malloc(sizeof(t_cmd));
			cmd->logic.right = (t_cmd *)malloc(sizeof(t_cmd));
			set_command(start_left, cmd->logic.left);
			set_command(start_right, cmd->logic.right);
			return (TRUE);
		}
		cursor = cursor->next;
	}
	return (FALSE);
}

t_bool redir(t_list *tokens, t_cmd *cmd)
{
	t_list	*cursor;
	int		tok_type;

	cursor = tokens;
	while (cursor->next != NULL)
	{
		cursor = skip_parentheses(cursor);
		tok_type = get_token_type((char *)cursor->next->content);
		// TODO dabors le out ? (ca devrait etre egal...)
		if (tok_type == REDIR_IN || tok_type == REDIR_OUT)
		{
			cmd->type = (t_cmd_type)tok_type;
			cmd->redir.filename = (char *)cursor->next->next->content;
			/* saute le `> file`, donc 2 tokens */
			cursor->next = cursor->next->next->next;
			cmd->redir.cmd = (t_cmd *)malloc(sizeof(t_cmd));
			set_command(tokens, cmd->redir.cmd);
			return (TRUE);
		}
		cursor = cursor->next;
	}
	return (FALSE);
}

t_bool	pipeline(t_list *tokens, t_cmd *cmd)
{
	// 1. get pipeline size
	t_list	*cursor;
	t_list	*argv_start;
	t_list	*argv_next;
	t_cmd	*cmd_cursor;
	t_cmd	*new_cmd;

	cmd->type = PIPELINE;
	cmd->pipeline.pipe_count = 0;
	cursor = tokens;
	while (cursor != NULL)
	{
		cursor = skip_parentheses(cursor);
		if (get_token_type((char *)cursor->content) == PIPELINE)
			cmd->pipeline.pipe_count++;
		cursor = cursor->next;
	}
	if (cmd->pipeline.pipe_count == 0)
		return (FALSE);

	// 2. set args
	argv_start = tokens;
	cursor = tokens;
	cmd_cursor = cmd;
	while (cursor->next != NULL)
	{
		if (get_token_type((char *)cursor->next->content) == PIPELINE)
		{
			argv_next = cursor->next->next;
			cursor->next = NULL;
			cursor = argv_next;

			new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
			set_command(argv_start, new_cmd);

			if (cmd_cursor->type == PIPELINE)
				cmd_cursor->pipeline.first_cmd = new_cmd;
			else
				cmd_cursor->cmd.next = new_cmd;
			cmd_cursor = new_cmd;
			argv_start = argv_next;
		}
		else
		{
			cursor = cursor->next;
		}
	}
	cmd_cursor->cmd.next = (t_cmd *)malloc(sizeof(t_cmd));
	set_command(argv_start, cmd_cursor->cmd.next);
	cmd_cursor = cmd_cursor->cmd.next;
	return (TRUE);
}


#include "../tests/debug_helper.h"
int	set_command(t_list *tokens, t_cmd *cmd)
{
	int		exit_status;

	exit_status = are_we_in_parentheses(tokens);
	if (exit_status == ERROR) /* ERROR = 1 */
		return (ERROR);
	else if (exit_status == USED) /* USED = 2 */
		tokens = skip_parentheses(tokens);
	exit_status = logic(tokens, cmd);
	if (exit_status == ERROR || exit_status == USED)
		return (exit_status);
	exit_status = redir(tokens, cmd);
	if (exit_status == ERROR || exit_status == USED)
		return (exit_status);
	exit_status = pipeline(tokens, cmd);
	if (exit_status == ERROR || exit_status == USED)
		return (exit_status);
	exit_status = parse_command(tokens, cmd);
	return (exit_status);
}

t_cmd *parser(t_list *tokens) {
	t_cmd	*cmd = (t_cmd*)malloc(sizeof(t_cmd));
	if (set_command(tokens, cmd) != SUCCESS)
	{
		// TODO
		return (NULL);
	}
	return (cmd);
}
