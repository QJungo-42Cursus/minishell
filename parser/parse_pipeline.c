#include "parser.h"

int number_of_pipe_operator(t_list *cursor)
{
	int		size;

	size = 0;
	while (cursor != NULL)
	{
		if (get_token_type((char *)cursor->content) == PIPELINE)
			size++;
		if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
			cursor = skip_parentheses(cursor);
		cursor = cursor->next;
	}
	return (size);
}

t_list	*set_pipeline_to_null_and_return_next(t_list *cursor)
{
	t_list		*next_node_is_null;

	while (cursor->next != NULL)
	{
		if (get_token_type((char *)cursor->next->content) == PIPELINE)
		{
			next_node_is_null = cursor;
			cursor = cursor->next->next;
			next_node_is_null->next = NULL;
			return (cursor);
		}
		cursor = cursor->next;
	}
	return (NULL);
}

int	set_pipeline_and_args(t_list *cursor, t_cmd *cmd, t_minishell *minishell)
{
	t_list		*start;
	t_cmd		*new_cmd;
	t_cmd		*cmd_cursor;

	start = cursor;
	cmd_cursor = cmd;
	while (TRUE)
	{
		if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
		{
			cursor  = skip_parentheses(cursor);
		}
		cursor = set_pipeline_to_null_and_return_next(cursor);
		if (cursor == NULL)
			break ;
		new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
		set_command(start, new_cmd, minishell);
		if (cmd_cursor->type == PIPELINE)
			cmd_cursor->pipeline.first_cmd = new_cmd;
		else
			cmd_cursor->cmd.next = new_cmd;
		cmd_cursor = new_cmd;
		start = cursor;
	}
	cmd_cursor->cmd.next = (t_cmd *)malloc(sizeof(t_cmd));
	set_command(start, cmd_cursor->cmd.next, minishell);
	cmd_cursor = cmd_cursor->cmd.next;
	return (SUCCESS);
}

int	pipeline(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	cmd->pipeline.pipe_count = number_of_pipe_operator(tokens);
	if (cmd->pipeline.pipe_count == 0)
		return (FALSE);
	cmd->pipeline.pipe_count++;
	cmd->type = PIPELINE;
	if (set_pipeline_and_args(tokens, cmd, minishell) == ERROR)
		return (ERROR);
	return (USED);
}
