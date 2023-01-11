/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 10:59:45 by qjungo            #+#    #+#             */
/*   Updated: 2022/07/14 10:59:45 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*v;
	size_t			i;

	v = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		v[i++] = (unsigned char)c;
	}
	return ((void *)v);
}
