/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:52:19 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:00:27 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_isprint(int c)
{
	if (c == 32)
		return (64);
	if (ft_isalnum(c))
		return (ft_isalnum(c));
	if (ft_isascii(c) && c > 32 && c < 127)
		return (16);
	return (0);
}
