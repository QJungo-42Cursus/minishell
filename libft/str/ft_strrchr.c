/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 11:05:29 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:03:08 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(char *str, int c)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	while (i <= len)
	{
		if (str[len - i] == (unsigned char)c)
			return (&str[len - i]);
		i++;
	}
	return (NULL);
}
