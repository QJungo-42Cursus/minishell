/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:41:36 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/11 09:34:15 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITER_H
# define WRITER_H
# include "../../../libft.h"
# include <stdarg.h>

int	writer(const t_list *words, va_list args, const char *string);
int	swriter(const t_list *words, va_list args, const char *string);

#endif /* WRITER_H */
