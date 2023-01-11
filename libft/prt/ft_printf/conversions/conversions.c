/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:33:36 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:14:07 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "../../../libft.h"
#include "../t_word.h"
#include "conversions.h"

static char	*string(char *string)
{
	if (string == 0)
		return (ft_strdup("(null)"));
	return (ft_strdup(string));
}

char	*conversions(const char *flag, va_list args)
{
	char	format_type;

	format_type = flag[ft_strlen(flag) - 1];
	if (format_type == '%')
		return (character('%'));
	if (format_type == 's')
		return (string(va_arg(args, char *)));
	if (format_type == 'u')
		return (utoa(va_arg(args, unsigned int)));
	if (format_type == 'd' || format_type == 'i')
		return (ft_itoa(va_arg(args, long long int)));
	if (format_type == 'x' || format_type == 'X')
		return (hexa(va_arg(args, unsigned long long int), format_type));
	if (format_type == 'p')
		return (pointer(va_arg(args, unsigned long long int)));
	if (format_type == 'c')
		return (character(va_arg(args, unsigned int)));
	return (NULL);
}
