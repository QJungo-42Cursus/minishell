/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_retokenize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:08:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 12:14:19 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser/parser.h"
#include <unistd.h>
#include "../tokenizer/tokenizer.h"
#include "../expansion/expansion.h"

char	*expand_o(t_minishell *minishell, t_list *tokens_ptr)
{
	char	*initial_token;
	char	*new_token;

	initial_token = (char *)tokens_ptr->content;
	new_token = expand(initial_token, minishell);
	tokens_ptr->content = new_token;
	if (ft_strncmp(new_token, initial_token, ft_strlen(initial_token)) == 0)
	{
		free(initial_token);
		return (NULL);
	}
	free(initial_token);
	return (new_token);
}

void	replace_expanded_token(t_list **tokens_ptr, t_list *new_tokens)
{
	t_list		*next;

	next = (*tokens_ptr)->next;
	(*tokens_ptr)->content = new_tokens->content;
	(*tokens_ptr)->next = new_tokens->next;
	(*tokens_ptr) = (*tokens_ptr)->next;
	while ((*tokens_ptr)->next != NULL)
		(*tokens_ptr) = (*tokens_ptr)->next;
	(*tokens_ptr)->next = next;
}

t_list	*expand_and_retokenize(t_list *tokens, t_minishell *minishell)
{
	t_list		*tokens_ptr;
	t_list		*new_tokens;
	char		*new_token;

	tokens_ptr = tokens;
	while (tokens_ptr != NULL)
	{
		new_token = expand_o(minishell, tokens_ptr);
		if (new_token && tokenizer(new_token, &new_tokens, TRUE) == ERROR)
			malloc_error(minishell);
		else if (new_token && new_tokens && new_tokens->next == NULL)
		{
			tokens_ptr->content = new_tokens->content;
			free(new_tokens);
		}
		else if (new_token != NULL && new_tokens != NULL)
			replace_expanded_token(&tokens_ptr, new_tokens);
		free(new_token);
		tokens_ptr = tokens_ptr->next;
	}
	return (tokens);
}
