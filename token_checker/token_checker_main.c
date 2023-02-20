#include "token_checker.h"

static int	check_parenthesis_order(t_list *token)
{
	int		open;
	t_list	*tmp;

	open = 0;
	tmp = token;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "(", 2) == 0)
			open++;
		if (ft_strncmp(tmp->content, ")", 2) == 0)
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

	open = count_separateur_in_tooken(token, "(");
	close = count_separateur_in_tooken(token, ")");
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

// Cette fonction a deux roles:
	// Verification que les pipes ne se trouvent pas aux debuts ou a la fin.
	// Verification que les pipes ne sont pas acotes. VERIFIER s'il n'y a pas d'erreurs.
// Deuxieme option: est peut etre deja gere par ta struct

static int	check_pipe_position(t_list *lst_token)
{
	int		close_index;
	int		len;
	t_list	*tmp;

	if (count_separateur_in_tooken(lst_token, "|") == 0)
		return (SUCCESS);
	len = ft_lstsize(lst_token);
	close_index = get_last_index_in_list(lst_token, len, "|");
	if (get_first_occurence_in_list(lst_token, "|") == 0 || close_index == len)
	{
		errno = EINVAL;
		perror("syntax error near unexpected tooken '|'");
		return (ERROR);
	}
	tmp = lst_token;
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "|", 2) != 0)
			tmp = tmp->next;
		else
		{
			if (ft_strncmp(tmp->next->content, "|", 2) == 0)
				return (ERROR);
			tmp = tmp->next;
		}
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
