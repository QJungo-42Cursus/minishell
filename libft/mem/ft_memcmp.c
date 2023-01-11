/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:14:15 by qjungo            #+#    #+#             */
/*   Updated: 2022/10/10 11:14:15 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*str_a;
	unsigned char	*str_b;
	int				diff;
	size_t			i;

	str_a = (unsigned char *)str1;
	str_b = (unsigned char *)str2;
	i = 0;
	while (i < n)
	{
		diff = str_a[i] - str_b[i];
		if (diff > 0)
			return (diff);
		if (diff < 0)
			return (diff);
		i++;
	}
	return (0);
}
