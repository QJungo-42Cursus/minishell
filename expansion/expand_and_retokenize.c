/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_retokenize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:08:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/25 18:00:56 by qjungo           ###   ########.fr       */
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

t_list	*weak_tokenizer(char *string)
{
	char	**tokens;
	t_list	*token_list;
	int		i;

	tokens = ft_split(string, ' ');
	if (tokens == NULL || tokens[0] == NULL)
		return (ft_lstnew(string));
	i = 0;
	token_list = NULL;
	ft_lstadd_back(&token_list, ft_lstnew(tokens[i]));
	i++;
	while (tokens[i] != NULL)
	{
		ft_lstadd_back(&token_list, ft_lstnew(tokens[i]));
		i++;
	}
	return (token_list);
}

t_list	*expand_and_retokenize(t_list *tokens, t_minishell *minishell)
{
	t_list		*tokens_ptr;
	t_list		*new_tokens;
	char		*new_token_c;

	tokens_ptr = tokens;
	while (tokens_ptr != NULL)
	{
		new_token_c = expand_o(minishell, tokens_ptr);
		if (new_token_c == NULL)
		{
			unquote((char *)tokens_ptr->content);
			tokens_ptr = tokens_ptr->next;
			continue ;
		}
		new_tokens = weak_tokenizer(new_token_c);
		if (new_tokens == NULL)
			malloc_error(minishell);
		if (new_tokens && new_tokens->next == NULL)
		{
			tokens_ptr->content = new_tokens->content;
			free(new_tokens);
			free(new_token_c);
		}
		else if (new_token_c && new_tokens)
		{
			replace_expanded_token(&tokens_ptr, new_tokens);
			free(new_tokens);
			free(new_token_c);
		}
		tokens_ptr = tokens_ptr->next;
	}
	return (tokens);
}
