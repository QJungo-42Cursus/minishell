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
	t_list		*new_tokens;
	t_list		*next;
	char		*new_token;

	tokens_ptr = tokens;
	while (tokens_ptr != NULL)
	{
		// expand
		initial_token = (char *)tokens_ptr->content;
		new_token = expand(initial_token, minishell);
		tokens_ptr->content = new_token;
		if (ft_strncmp(new_token, initial_token, ft_strlen(initial_token)) == 0)
		{
			tokens_ptr = tokens_ptr->next;
			free(initial_token);
			continue ;
		}
		free(initial_token);

		// retokenize and replace
		new_tokens = tokenizer(new_token, TRUE);
		if (new_tokens == NULL)
		{
			tokens_ptr = tokens_ptr->next;
			continue ;
		}
		if (new_tokens->next == NULL) // new_tokens taille : 1
		{
			tokens_ptr->content = new_tokens->content;
			free(new_token);
			free(new_tokens);
		}
		else
		{
			next = tokens_ptr->next;
			tokens_ptr->content = new_tokens->content;
			free(new_token);
			tokens_ptr->next = new_tokens->next;
			tokens_ptr = tokens_ptr->next;
			while (tokens_ptr->next != NULL)
				tokens_ptr = tokens_ptr->next;
			tokens_ptr->next = next;
		}
			//free(new_token);
		tokens_ptr = tokens_ptr->next;
	}
	return tokens;
}

#define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token `"

int	is_heredoc_valid(t_list *cursor, t_cmd *cmd)
{
	(void)cmd;
	char	*token;

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
	// TODO plein de cas a ajouter !
}

int	is_token_valid(char *token, t_list *cursor, t_cmd *cmd)
{
	if (get_token_type(token) == OPEN_PARENTHESES)
	{
		write(STDERR_FILENO, UNEXPECTED_TOKEN, 47);
		if (cursor->next == NULL)
			write(STDERR_FILENO, "newline", 7);
		else
			write(STDERR_FILENO, (char *)cursor->next->content, ft_strlen((char *)cursor->next->content));
		write(STDERR_FILENO, "'\n", 2);
		return (FALSE);
	}
	if (get_token_type(token) == CLOSE_PARENTHESES)
	{
		write(STDERR_FILENO, UNEXPECTED_TOKEN, 47);
		write(STDERR_FILENO, token, ft_strlen(token));
		write(STDERR_FILENO, "'\n", 2);
		return (FALSE);
	}

	if (get_token_type(token) == HEREDOC)
	{
		return (is_heredoc_valid(cursor->next, cmd));
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


char	*get_heredoc_input(char *delimiter)
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
		int delimiter_len = ft_strlen(delimiter);
		if (ft_strncmp(line, delimiter, delimiter_len) == 0 && line[delimiter_len] == '\n' && ft_strlen(line) == delimiter_len + 1) 
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
	cmd->cmd.heredoc = get_heredoc_input((char *)(*cursor)->next->content);
	if (cmd->cmd.heredoc == NULL)
		return (ERROR);
	*cursor = (*cursor)->next->next;
	return (USED);
}

int	parse_command(t_list *tokens, t_cmd *cmd, t_minishell *minishell)
{
	t_list	*cursor;
	int		i;
	char	*token;
	int		get_heredoc_res;

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
		token = (char *)cursor->content;
		if (!is_token_valid(token, cursor, cmd))
		{
			free(cmd->cmd.argv);
			return (ERROR);
		}
		get_heredoc_res = get_heredoc(&cursor, cmd);
		if (get_heredoc_res == ERROR)
		{
			// TODO
			free(cmd->cmd.argv);
			return (ERROR);
		}
		if (get_heredoc_res == USED)
			continue ;
		cmd->cmd.argv[i] = (char *)cursor->content;
		cursor = cursor->next;
		i++;
	}
	cmd->cmd.argv[i] = NULL;
	cmd->cmd.next = NULL;
	cmd->cmd.heredoc = NULL;
	return (SUCCESS);
}
