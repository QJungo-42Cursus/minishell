#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../libft/libft.h"
#include "../tokenizer/tokenizer.h"
#include "../expansion/expansion.h"

t_list	*expand_and_retokenize(t_list *tokens, t_minishell *minishell)
{
	t_list		*tokens_ptr;
	char		*initial_token;

	tokens_ptr = tokens;
	while (tokens_ptr != NULL)
	{
		// expand
		initial_token = (char *)tokens_ptr->content;
		tokens_ptr->content = expand(initial_token, (const char **)minishell->env_copy);
		if (ft_strncmp((char *)tokens_ptr->content, initial_token, ft_strlen(initial_token)) == 0)
		{
			tokens_ptr = tokens_ptr->next;
			free(initial_token);
			continue ;
		}

		free(initial_token);

		// retokenize
		t_list	*new_tokens;
		new_tokens = tokenizer((char *)tokens_ptr->content, TRUE);

		// replace tokens
		if (new_tokens->next == NULL) // new_tokens taille : 1
		{
			tokens_ptr->content = new_tokens->content;
			free(new_tokens);
		}
		else
		{
			t_list *next = tokens_ptr->next;
			tokens_ptr->content = new_tokens->content;
			tokens_ptr->next = new_tokens->next;
			//free(new_tokens);
			tokens_ptr = tokens_ptr->next;
			while (tokens_ptr->next != NULL)
				tokens_ptr = tokens_ptr->next;
			tokens_ptr->next = next;
		}
		tokens_ptr = tokens_ptr->next;
	}
	return tokens;
}

static int	is_token_valid(char *token, t_list *cursor)
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


void	print_resti(t_list *cursor)
{
	printf("[");
	while (cursor != NULL)
	{
		printf("%s, ", (char *)cursor->content);
		cursor = cursor->next;
	}
	printf("]\n");
}

int	parse_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	t_list	*cursor;
	int		i;

	//print_resti(tokens); //
	tokens = expand_and_retokenize(tokens, minishell);
	cursor = tokens;
	while  (cursor != NULL)
	{
		unquote((char *)cursor->content);
		cursor = cursor->next;
	}

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
