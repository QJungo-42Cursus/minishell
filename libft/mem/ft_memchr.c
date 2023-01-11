/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:00:13 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:09:00 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*cstr;
	unsigned char	cc;

	cstr = (unsigned char *)str;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (cstr[i] == cc)
			return (&cstr[i]);
		i++;
	}
	return (NULL);
}
