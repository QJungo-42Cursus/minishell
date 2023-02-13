
#include "token_checker.h"

int	check_valid(t_list *input_tooken)
{
	int	open;
	int	close;
	int	len;

	len = ft_lstsize(input_tooken);
	open = count_separateur_in_tooken(input_tooken, "(");
	close = count_separateur_in_tooken(input_tooken, ")");
	if (open != close)
	{
		errno = EINVAL;
		perror("syntax error near unexpected tooken '()'");
		return (ERROR);
	}
	if (count_separateur_in_tooken(input_tooken, "|") != 0)
	{
		open = get_first_occurence_in_list(input_tooken, "|");
		close = get_last_index_in_list(input_tooken, len, "|");
		if (open == 0 || close == len)
		{
			errno = EINVAL;
			perror("syntax error near unexpected tooken '|'");
			return (ERROR);
		}
	}
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
