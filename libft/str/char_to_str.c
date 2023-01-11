/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_to_str_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 10:48:49 by qjungo            #+#    #+#             */
/*   Updated: 2022/10/27 10:09:21 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*char_to_str(char c)
{
	char	*res;

	res = malloc(2);
	if (res == NULL)
		return (NULL);
	res[0] = c;
	res[1] = '\0';
	return (res);
}
