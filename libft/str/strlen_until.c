/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_until.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:52:43 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:09:14 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	strlen_until(const char *string, const char *charset)
{
	int		len;

	len = 0;
	while (string[len] && !is_in_charset(string[len], charset))
		len++;
	return (len);
}
