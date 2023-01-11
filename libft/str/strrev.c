/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrev.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:13:06 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:06:55 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "../libft.h"

void	strrev(char *string)
{
	int		len;
	int		i;
	char	temp;

	len = ft_strlen(string);
	i = 0;
	while (i < len / 2)
	{
		temp = string[len - i - 1];
		string[len - i - 1] = string[i];
		string[i] = temp;
		i++;
	}
}
