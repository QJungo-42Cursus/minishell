/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:34:26 by qjungo            #+#    #+#             */
/*   Updated: 2022/10/19 10:43:23 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSIONS_H
# define CONVERSIONS_H
# include <stdarg.h>

char	*conversions(const char *flag, va_list args);
char	*hexa(unsigned int val, char format_type);
char	*character(unsigned int c);
char	*pointer(unsigned long long int p);

#endif /* CONVERSIONS_H */
