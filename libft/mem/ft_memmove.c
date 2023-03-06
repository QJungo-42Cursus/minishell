/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 10:59:40 by qjungo            #+#    #+#             */
/*   Updated: 2022/10/11 10:45:57 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest_ptr;
	char		*src_ptr;

	if (!dest && !src)
		return (dest);
	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	i = -1;
	if (dest > src)
		while (++i < n)
			dest_ptr[n - i - 1] = src_ptr[n - i - 1];
	else
		while (++i < n)
				dest_ptr[i] = src_ptr[i];
	return (dest);
}
