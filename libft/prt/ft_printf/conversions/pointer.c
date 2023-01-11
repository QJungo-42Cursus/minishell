/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:19:38 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:14:07 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft.h"
#include "../t_word.h"

char	*pointer(unsigned long long int p)
{
	char	*res;
	char	*itoa;

	itoa = itoa_base(p, "0123456789abcdef", 16);
	if (itoa == NULL)
		return (NULL);
	res = ft_strjoin("0x", itoa);
	free(itoa);
	return (res);
}
