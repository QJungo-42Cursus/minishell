/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:52:01 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:08:43 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "../libft.h"
#ifndef SIZE_MAX
# ifdef __SIZE_MAX__
#  define SIZE_MAX __SIZE_MAX__
# elif
#  define SIZE_MAX 18446744073709551615
# endif
#endif

// TODO clarifier pourquoi les SIZE_MAX sont utiles ?
void	*ft_calloc(size_t nmem, size_t size)
{
	unsigned char		*res;

	if (nmem == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	res = malloc(nmem * size);
	if (res == NULL)
		return (NULL);
	ft_memset(res, 0, (nmem * size));
	return (res);
}
