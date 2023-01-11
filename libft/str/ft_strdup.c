/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:52:36 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:02:37 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(char *string)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (ft_strlen(string) + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (string[i])
	{
		res[i] = string[i];
		i++;
	}
	res[i] = 0;
	return (res);
}
