/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:10:51 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:41:56 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *n)
{
	t_list	*ptr;

	ptr = ft_lstlast(*lst);
	if (ptr == NULL)
	{
		*lst = n;
		return ;
	}
	ptr->next = n;
}

/*
 *
 #1.  The address of a pointer to the first link ofa list.
 #2.  The address of a pointer to the element to be added to the list.

 Return valueNone

 External functs.None

 Description
 Adds the element ’new’ at the end of the list.
 */
