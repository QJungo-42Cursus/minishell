/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:57:21 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/08 10:58:23 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

long	long_atoi(const char *string)
{
	long		result;
	int			i;
	int			minus;

	result = 0;
	i = 0;
	minus = 1;
	while (is_in_charset(string[i], " \t\n\r\v\f"))
		i++;
	if (string[i] == '-')
	{
		minus = -minus;
		i++;
	}
	else if (string[i] == '+')
		i++;
	while (is_in_charset(string[i], "0123456789"))
	{
		result = result * 10 + string[i] - 48;
		i++;
	}
	return (result * minus);
}
