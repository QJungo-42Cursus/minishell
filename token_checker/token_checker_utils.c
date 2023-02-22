
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

int	count_separateur_in_tooken(t_list *lst, char *sep)
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
