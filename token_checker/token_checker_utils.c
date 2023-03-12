/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:21:08 by agonelle          #+#    #+#             */
/*   Updated: 2023/02/25 18:02:45 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_checker.h"

int	get_first_occurence_in_list(t_list *lst, char *sep)
{
	int	index;

	index = 0;
	while (lst)
	{
		if (!ft_strncmp((char *)lst->content, sep, ft_strlen(sep)))
			return (index);
		index++;
		lst = lst->next;
	}
	return (index);
}

int	get_last_index_in_list(t_list *lst, int len, char *sep)
{
	int	index;
	int	i;

	index = 0;
	i = 0;
	while (lst && i < len)
	{
		if (!ft_strncmp((char *)lst->content, sep, ft_strlen(sep)))
			index = i + 1 ;
		lst = lst->next;
		i++;
	}
	return (index);
}

int	count_separateur_in_token(t_list *lst, char *sep)
{
	int	count;

	count = 0;
	while (lst)
	{
		if (!ft_strncmp((char *)lst->content, sep, ft_strlen(sep) + 1))
			count++;
		lst = lst->next;
	}
	return (count);
}

t_bool	are_two_pipe_consecutive(t_list *current)
{
	char	*current_token;
	char	*next_token;

	current_token = (char *)current->content;
	if (ft_strncmp(current_token, (char *)"|", 2) != 0)
		current_token = NULL;
	if (current->next == NULL)
		next_token = NULL;
	else
		next_token = (char *)current->next->content;
	if (next_token && ft_strncmp(next_token, (char *)"|", 2) != 0)
		next_token = NULL;
	return ((t_bool)(current_token && next_token));
}
