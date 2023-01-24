#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../libft/libft.h"

int	is_token_valid(char *token, t_list *cursor)
{
	if (get_token_type(token) == OPEN_PARENTHESES)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
		if (cursor->next == NULL)
			write(STDERR_FILENO, "newline", 7);
		else
			write(STDERR_FILENO, (char *)cursor->next->content, ft_strlen((char *)cursor->next->content));
		write(STDERR_FILENO, "'\n", 2);
		return (FALSE);
	}
	if (get_token_type(token) == CLOSE_PARENTHESES)
	{
		write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
		write(STDERR_FILENO, token, ft_strlen(token));
		write(STDERR_FILENO, "'\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

int	parse_command(t_list *tokens, t_cmd *cmd)
{
	t_list	*cursor;
	int		i;

	cmd->type = COMMAND;
	cmd->cmd.argv = (char **)malloc(sizeof(char *) * (ft_lstsize(tokens) + 1));
	cursor = tokens;
	i = 0;
	while (cursor != NULL)
	{
		cmd->cmd.argv[i] = (char *)cursor->content;
		if (!is_token_valid(cmd->cmd.argv[i], cursor))
		{
			free(cmd->cmd.argv);
			return (ERROR);
		}
		cursor = cursor->next;
		i++;
	}
	cmd->cmd.argv[i] = NULL;
	cmd->cmd.next = NULL;
	return (SUCCESS);
}
