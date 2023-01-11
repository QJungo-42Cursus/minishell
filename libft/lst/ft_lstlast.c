/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:16:15 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:04:50 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
 *
 ft_lstlastPrototypet_list *ft_lstlast(t_list *lst);

 Turn in files-

 #1.  The beginning of the list.

 Return value Last element of the list.

 External functs.None

 Description
 Returns the last element of the list

 */
