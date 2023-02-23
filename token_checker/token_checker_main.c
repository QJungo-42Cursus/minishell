/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:52:31 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:52:32 by qjungo           ###   ########.fr       */
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

static t_bool	are_two_pipe_consecutive(t_list *current)
{
	char	*current_token;
	char	*next_token;

	current_token = (char *)current->content;
	next_token = (char *)current->next->content;
	return ((t_bool)(ft_strncmp(current_token, (char *)"|", 2) == 0
		&& ft_strncmp(next_token, (char *)"|", 2) == 0));
}

// Cette fonction a deux roles:
	// les pipes ne se trouvent pas aux debuts ou a la fin.
	// les pipes ne sont pas acotes. VERIFIER s'il n'y a pas d'erreurs.
// Deuxieme option: est peut etre deja gere par ta struct
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

int	check_valid_tokens(t_list *input_tooken)
{
	if (check_parenthesis(input_tooken) == ERROR)
		return (ERROR);
	if (check_pipe_position(input_tooken) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
// TODO -> c'est token, pas tooken
