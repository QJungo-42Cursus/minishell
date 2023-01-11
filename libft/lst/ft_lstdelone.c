/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:18:42 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:04:50 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}

//Turn in files-Parameters
//
// #1.  The element to free.
// #2.  The address of the function used to delete the content.
// Return valueNone
// External functs.free
//
// Description
// Takes as a parameter an element and frees the
// memory of the element’s content using the function ’del’ given
// as a parameter and free the element.
// The memory of ’next’ must not be freed
