/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:11:42 by agonelle          #+#    #+#             */
/*   Updated: 2023/03/15 11:41:28 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_checker.h"

static int	check_pipe_position(t_list *lst_token)
{
	int		close_index;
	int		len;
	t_list	*tmp;

	if (count_separateur_in_token(lst_token, (char *)"|") == 0)
		return (SUCCESS);
	len = ft_lstsize(lst_token);
	close_index = get_last_index_in_list(lst_token, len, (char *)"|");
	if (get_first_occurence_in_list(lst_token, (char *)"|") == 0
		|| close_index == len)
	{
		errno = EINVAL;
		perror("syntax error near unexpected token '|'");
		return (ERROR);
	}
	tmp = lst_token;
	while (tmp)
	{
		if (are_two_pipe_consecutive(tmp))
			return (ERROR);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

#define E_SYN "syntax error near unexpected token"

static int	err_(char *tok)
{
	ft_putstr_fd(STR E_SYN" `", 2);
	ft_putstr_fd(STR tok, 2);
	ft_putstr_fd(STR"'\n", 2);
	return (ERROR);
}

static int	check_heredoc_alone(t_list *tmp)
{
	int		is_first;

	is_first = TRUE;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, (char *)"<<", 3) == 0)
		{
			if (tmp->next == NULL)
			{
				ft_putstr_fd(STR""E_SYN" `newline'\n", 2);
				return (ERROR);
			}
			if (is_first && (tmp->next == NULL || tmp->next->next == NULL))
				return (err_(tmp->next->content));
			if (ft_strncmp((char *)tmp->next->content, (char *)"<<", 3) == 0)
			{
				ft_putendl_fd(STR"syntax error near unexpected token '<<'", 2);
				return (ERROR);
			}
		}
		is_first = FALSE;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_valid_tokens(t_list *input_token)
{
	if (check_pipe_position(input_token) == ERROR)
		return (ERROR);
	if (check_heredoc_alone(input_token) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
