/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:42 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/25 16:05:57 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include "../env/env.h"
#include <stdlib.h>
#include <stdio.h>
#include "expansion.h"

static char	*get_all(t_position index,
		char *new_token_tmp, char *new_token, t_minishell *minishell)
{
	while (get_var_position(index.end, new_token_tmp, &index.start, &index.end))
	{
		if (index.start - index.end == 0)
		{
			free(new_token_tmp);
			break ;
		}
		new_token = expand_dollar(new_token_tmp, minishell, index);
		free(new_token_tmp);
		if (new_token == NULL)
			return (ft_strdup((char *)""));
		new_token_tmp = new_token;
	}
	return (new_token);
}

static char	*get_expanded_dollars(const char *token, t_minishell *minishell)
{
	t_position	index;
	char		*new_token;
	char		*new_token_tmp;

	new_token = NULL;
	new_token_tmp = ft_strdup((char *)token);
	if (new_token_tmp == NULL)
		return (NULL);
	if (get_var_position(0, new_token_tmp, &index.start, &index.end) == FALSE)
	{
		free(new_token_tmp);
		return (ft_strdup((char *)token));
	}
	index.start = 0;
	index.end = 0;
	return (get_all(index, new_token_tmp, new_token, minishell));
}

char	*expand(const char *token, t_minishell *minishell)
{
	char	*expanded;

	expanded = get_expanded_dollars(token, minishell);
	if (expanded == NULL)
	{
		expanded = ft_strdup((char *)token);
		if (expanded == NULL)
			return (NULL);
	}
	return (expanded);
}
