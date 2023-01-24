#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../libft/libft.h"

int	parse_command(t_list *tokens, t_cmd *cmd)
{
	t_list	*cursor;
	int		i;
	char	*err_msg;

	cmd->type = COMMAND;
	cmd->cmd.argv = (char **)malloc(sizeof(char *) * (ft_lstsize(tokens) + 1));
	cursor = tokens;
	i = 0;
	while (cursor != NULL)
	{
		cmd->cmd.argv[i] = (char *)cursor->content;
		cursor = cursor->next;
		if (get_token_type(cmd->cmd.argv[i]) == OPEN_PARENTHESES)
		{
			free(cmd->cmd.argv);
			err_msg = ft_sprintf("minishell: syntax error near unexpected token `%s'", (char *)cursor->content);
			ft_putendl_fd(err_msg, STDERR_FILENO);
			free(err_msg);
			return (ERROR);
		}
		if (get_token_type(cmd->cmd.argv[i]) == CLOSE_PARENTHESES)
		{
			err_msg = ft_sprintf("minishell: syntax error near unexpected token `%s'", cmd->cmd.argv[i]);
			ft_putendl_fd(err_msg, STDERR_FILENO);
			free(cmd->cmd.argv);
			free(err_msg);
			return (ERROR);
		}

		i++;
	}
	cmd->cmd.argv[i] = NULL;
	cmd->cmd.next = NULL;
	return (SUCCESS);
}
