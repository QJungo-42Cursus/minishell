/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:11 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/09 14:26:05 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"
#include "../libft/libft.h"
#include "../minishell.h"

int	get_token_type(char *token)
{
	if (ft_strncmp(token, "(", 2) == 0)
		return (OPEN_PARENTHESES);
	else if (ft_strncmp(token, ")", 2) == 0)
		return (CLOSE_PARENTHESES);
	else if (ft_strncmp(token, "&&", 3) == 0)
		return (LOGIC_AND);
	else if (ft_strncmp(token, "||", 3) == 0)
		return (LOGIC_OR);
	else if (ft_strncmp(token, "|", 2) == 0)
		return (PIPELINE);
	else if (ft_strncmp(token, ">>", 3) == 0)
		return (REDIR_APPEND);
	else if (ft_strncmp(token, "<<", 3) == 0)
		return (HEREDOC);
	else if (ft_strncmp(token, "<", 2) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(token, ">", 2) == 0)
		return (REDIR_OUT);
	else
		return (COMMAND);
}

t_bool	are_we_in_parentheses(t_list *tokens)
{
	t_list		*cursor;
	int			parentheses;

	if (tokens == NULL)
	{
		printf("exit at function : %s()\n", __func__);
		exit(222); ///
		return (FALSE);
	}
	if (get_token_type((char *)tokens->content) != OPEN_PARENTHESES)
		return (FALSE);
	cursor = tokens;
	parentheses = 0;
	while (cursor != NULL)
	{
		if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
			parentheses++;
		else if (get_token_type((char *)cursor->content) == CLOSE_PARENTHESES)
			parentheses--;
		if (parentheses == 0 && cursor->next == NULL)
			return (TRUE);
		if (parentheses == 0 && cursor->next != NULL)
			return (FALSE);
		cursor = cursor->next;
	}
	return (FALSE);
}

/* renvoie un pointeur sur le token ")" fermant le 1er groupe de parentheses 
 * si pas de parentheses des le debut, renvoie le meme pointeur
 * si pas de parentheses fermantes, renvoie le dernier token
 */
t_list	*skip_parentheses(t_list *cursor)
{
	int			parentheses;

	if (get_token_type((char *)cursor->content) != OPEN_PARENTHESES)
		return (cursor);
	parentheses = 1;
	while (parentheses > 0 && cursor->next != NULL)
	{
		cursor = cursor->next;
		if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
			parentheses++;
		else if (get_token_type((char *)cursor->content) == CLOSE_PARENTHESES)
			parentheses--;
	}
	return (cursor);
}

/// une sorte de "trim", ca enleve le debut et la fin de la t_list
/// return le pointeur sur le 1er token (apres cut) de la t_list
t_list	*lst_cut_first_and_last(t_list *tokens)
{
	t_list		*cursor;

	cursor = tokens;
	while (cursor->next->next != NULL)
		cursor = cursor->next;
	cursor->next = NULL;
	cursor = tokens->next;
	return (cursor);
}

