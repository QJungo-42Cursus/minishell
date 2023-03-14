/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_and_retokenize.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:22:11 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/14 18:15:56 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void	retokenize(t_list *cursor, char **split, t_minishell *minishell)
{
	int		i;
	t_list	*new;
	t_list	*next;

	next = cursor->next;
	free(cursor->content);
	cursor->content = split[0];
	i = 1;
	while (split[i] != NULL)
	{
		new = ft_lstnew(split[i]);
		if (new == NULL)
			malloc_error(minishell);
		append_to_free_list(minishell, new);
		cursor->next = new;
		cursor = new;
		i++;
	}
	free(split);
	cursor->next = next;
}

void	split_and_retokenize(t_list *cursor, t_minishell *msh)
{
	char	**split;

	split = ft_split((char *)cursor->content, ' ');
	if (split == NULL)
		malloc_error(msh);
	if (split[0] == NULL || split[1] == NULL)
	{
		if (split[0] != NULL)
			free(split[0]);
		free(split);
		return ;
	}
	retokenize(cursor, split, msh);
}

static int	shortest_string(char *a, char *b)
{
	if (ft_strlen(a) < ft_strlen(b))
		return (ft_strlen(a));
	return (ft_strlen(b));
}

void	expand_and_retokenize(t_list **tokens, t_minishell *minishell)
{
	t_list	*cursor;
	t_list	*last;
	char	*copy;

	last = NULL;
	cursor = *tokens;
	while (cursor != NULL)
	{
		copy = ft_strdup((char *)cursor->content);
		expand((char **)&cursor->content, minishell);
		if (ft_strlen(cursor->content) == 0)
		{
			if (last == NULL)
				*tokens = cursor->next;
			else
				last->next = cursor->next;
			free(cursor->content);
			cursor = cursor->next;
			continue ;
		}
		if (ft_strncmp((char *)cursor->content, copy, shortest_string((char *)cursor->content, copy) + 1) != 0) //TODO sur du +1 ?
		{
			split_and_retokenize(cursor, minishell);
		}
		unquote((char *)cursor->content);
		last = cursor;
		cursor = cursor->next;
	}
}
