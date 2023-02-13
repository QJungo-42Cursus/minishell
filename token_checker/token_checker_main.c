
#include "token_checker.h"

static int	check_parenthesis(t_list *token)
{
	int	open;
	int	close;

	open = count_separateur_in_tooken(token, "(");
	close = count_separateur_in_tooken(token, ")");
	if (open != close)
	{
		errno = EINVAL;
		perror("syntax error near unexpected tooken '()'");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	check_pipe_position(t_list *lst_token)
{
	int		close_index;
	int		len;
	t_list	*tmp;

	if (count_separateur_in_tooken(lst_token, "|") == 0)
		return (SUCCESS);
	len = ft_lstsize(lst_token);
	// Verification que les pipes ne se trouvent pas aux debuts ou a la fin.
	close_index = get_last_index_in_list(lst_token, len, "|");
	if (get_first_occurence_in_list(lst_token, "|") == 0 || close_index == len)
	{
		errno = EINVAL;
		perror("syntax error near unexpected tooken '|'");
		return (ERROR);
	}
	tmp = lst_token;
	// Verification que les pipes ne sont pas acotes. VERIFIER s'il n'y a pas d'erreurs.
	while (tmp)
	{
		if (ft_strncmp(tmp->content, "|", 2) != 0)
			tmp = tmp->next;
		else
			if (ft_strncmp(tmp->next->content, "|", 2) == 0)
				return (ERROR);
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

int	get_first_occurence_in_list(t_list *lst, char *sep)
{
	int	index;

	index = 0;
	while (lst)
	{
		if (!ft_strncmp(lst->content, sep, ft_strlen(sep)))
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
		if (!ft_strncmp(lst->content, sep, ft_strlen(sep)))
			index = i + 1 ;
		lst = lst->next;
		i++;
	}
	return (index);
}

int	count_separateur_in_tooken(t_list *lst, char *sep)
{
	int	count;

	count = 0;
	while (lst)
	{
		if (!ft_strncmp(lst->content, sep, ft_strlen(sep) + 1))
			count++;
		lst = lst->next;
	}
	return (count);
}
