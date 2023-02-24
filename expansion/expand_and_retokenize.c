#include "../parser/parser.h"
#include <unistd.h>
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
		if (tokenizer(new_token, &new_tokens, TRUE) == ERROR)
		{
			// TODO

		}
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
		tokens_ptr = tokens_ptr->next;
	}
	return (tokens);
}
