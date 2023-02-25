/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 12:11:42 by agonelle          #+#    #+#             */
/*   Updated: 2023/02/25 12:20:51 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_checker.h"

static int	check_parenthesis_order(t_list *token)
{
	int		open;
	t_list	*tmp;

	open = 0;
	tmp = token;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, (char *)"(", 2) == 0)
			open++;
		if (ft_strncmp((char *)tmp->content, (char *)")", 2) == 0)
			open--;
		if (open < 0)
		{
			errno = EINVAL;
			perror("syntax error near unexpected tooken ')'");
			return (ERROR);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static int	check_parenthesis(t_list *token)
{
	int		open;
	int		close;

	open = count_separateur_in_tooken(token, (char *)"(");
	close = count_separateur_in_tooken(token, (char *)")");
	if (open != close)
	{
		errno = EINVAL;
		perror("syntax error near unexpected tooken '()'");
		return (ERROR);
	}
	if (check_parenthesis_order(token) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	check_pipe_position(t_list *lst_token)
{
	int		close_index;
	int		len;
	t_list	*tmp;

	if (count_separateur_in_tooken(lst_token, (char *)"|") == 0)
		return (SUCCESS);
	len = ft_lstsize(lst_token);
	close_index = get_last_index_in_list(lst_token, len, (char *)"|");
	if (get_first_occurence_in_list(lst_token, (char *)"|") == 0
		|| close_index == len)
	{
		errno = EINVAL;
		perror("syntax error near unexpected tooken '|'");
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

static int	check_heredoc_alone(t_list *tmp)
{
	int		is_first;

	is_first = TRUE;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, (char *)"<<", 3) == 0)
		{
			if (is_first && (tmp->next == NULL || tmp->next->next == NULL))
			{
				ft_putstr_fd("syntax error near unexpected tooken '", 2);
				ft_putstr_fd((char *)tmp->next->content, 2);
				ft_putstr_fd("'\n", 2);
				return (ERROR);
			}
			if (ft_strncmp((char *)tmp->next->content, (char *)"<<", 3) == 0)
			{
				ft_putendl_fd("syntax error near unexpected tooken '<<'", 2);
				return (ERROR);
			}
		}
		is_first = FALSE;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

int	check_valid_tokens(t_list *input_tooken)
{
	if (check_parenthesis(input_tooken) == ERROR)
		return (ERROR);
	if (check_pipe_position(input_tooken) == ERROR)
		return (ERROR);
	if (check_heredoc_alone(input_tooken) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
