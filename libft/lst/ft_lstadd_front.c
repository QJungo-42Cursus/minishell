/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:11:06 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:42:10 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_front(t_list **lst, t_list *n)
{
	n->next = *lst;
	*lst = n;
}
/*
 * ft_lstadd_frontPrototypevoid
 ft_lstadd_front(t_list **lst, t_list *new);Turn in files-
 * Parameters
 * #1.  The address of a pointer to the first link of a list.
 * #2.  The address of a pointer to the element to beadded to the list.
 *
 * Return valu
 * eNone
 *
 * External functs.None
 * Description Adds the element ’new’ at the beginning of the list.
 * */
