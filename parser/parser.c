#include <stdio.h>
#include "parser.h"
#include <unistd.h>
#include "../libft/libft.h"
#include "../expansion/expansion.h"

int	logic(t_list *cursor, t_cmd *cmd)
{
	int			tok_type;
	t_list		*start_left = cursor;
	t_list		*start_right = cursor;

	while (cursor->next != NULL)
	{
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
			return (USED);
		}
		cursor = cursor->next;
	}
	return (FALSE);
}

int redir(t_list *tokens, t_cmd *cmd)
{
	t_list	*cursor;
	int		tok_type;

	cursor = tokens;
	while (cursor->next != NULL)
	{
		tok_type = get_token_type((char *)cursor->next->content);
		if (tok_type == REDIR_IN || tok_type == REDIR_OUT)
		{
			cmd->type = (t_cmd_type)tok_type;
			cmd->redir.filename = (char *)cursor->next->next->content;
			cursor->next = cursor->next->next->next;
			cmd->redir.cmd = (t_cmd *)malloc(sizeof(t_cmd));
			set_command(tokens, cmd->redir.cmd);
			return (USED);
		}
		cursor = cursor->next;
	}
	return (FALSE);
}

void	print_rest(t_list *cursor)
{
	while (cursor != NULL)
	{
		printf("%s ", (char *)cursor->content);
		cursor = cursor->next;
	}
	printf("\n");
}

int	set_command(t_list *tokens, t_cmd *cmd)
{
	int		exit_status;
	//print_rest(tokens);

	if (are_we_in_parentheses(tokens))
	{
		if (ft_strncmp((char *)tokens->next->content, ")", 2) == 0)
		{
			// TODO
			write(2, "minishell: syntax error near unexpected token `)'\n", 50);
			return (EXIT_FAILURE);
		}
		tokens = lst_cut_first_and_last(tokens);
	}
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

t_list	*get_last(t_list *list, t_list *current)
{
	t_list	*ptr;

	ptr = list;
	while (ptr->next != current && ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

#include "../tokenizer/tokenizer.h"
t_list	*expand_and_retokenize(t_list *tokens, t_minishell *minishell)
{
	t_list		*tokens_ptr;
	t_list		*new_tokens;

	char		*initial_token;
	char		*expanded_token;
	char		*expanded_token_with_dquotes;
	//char		*retokenized_token;

	t_bool		was_expanded;

	tokens_ptr = tokens;

	while (tokens_ptr != NULL)
	{
		// IL faut les "re-tokenizer" mais en partant du principe que c'est des mot
		printf("token before: %s\n", (char *)tokens_ptr->content);
		initial_token = (char *)tokens_ptr->content;
		expanded_token = expand(initial_token, (const char **)minishell->env_copy);

		was_expanded = (ft_strncmp(initial_token, expanded_token, ft_strlen(initial_token)) != 0);
		if (was_expanded)
		{
			//expanded_token_with_dquotes = ft_sprintf("\"%s\"", expanded_token);
			expanded_token_with_dquotes = ft_sprintf("%s", expanded_token);
			printf("token %s expanded_token_with_dquotes: %s\n", initial_token, expanded_token_with_dquotes);
			new_tokens = tokenizer(expanded_token_with_dquotes);
			printf("new_tokens[0]: %s\n", (char *)new_tokens->content);
			

			// replace the old el by the new list
			t_list	*after = tokens_ptr->next;
			printf("after: %s\n", after ? (char *)after->content : "null");
			tokens_ptr = get_last(tokens, tokens_ptr);
			printf("get_last: %s\n", (char *)tokens_ptr->content);
			tokens_ptr->next = new_tokens;
			printf("in new list: ");
			while (tokens_ptr->next != NULL)
			{
				printf("%s ", (char *)tokens_ptr->content);
				tokens_ptr = tokens_ptr->next;
			}
			printf("\n");
			tokens_ptr->next = after;
			printf("token after: %s\n", (char *)tokens_ptr->content);
			tokens_ptr = after;
		}
		else
		{
			printf("token after: %s\n", (char *)tokens_ptr->content);
			tokens_ptr = tokens_ptr->next;
		}
		printf("\n");
	}
	return tokens;
}

t_cmd *parser(t_list *tokens, t_minishell *minishell) 
{
	t_cmd	*cmd = (t_cmd*)malloc(sizeof(t_cmd));

	// TODO dans le main ?
	//tokens = expand_and_retokenize(tokens, minishell);
	(void)minishell;

	if (set_command(tokens, cmd) == ERROR)
	{
		// TODO
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
