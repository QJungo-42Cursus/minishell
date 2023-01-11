/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:19:28 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:14:07 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft.h"

char	*hexa(unsigned int val, char format_type)
{
	if (format_type == 'X')
		return (itoa_base(val, "0123456789ABCDEF", 16));
	else
		return (itoa_base(val, "0123456789abcdef", 16));
}
