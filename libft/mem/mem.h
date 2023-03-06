/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:44:19 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/06 19:28:17 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H
# include <stdlib.h>

void	split_free(char **list);
void	*ft_memmove(void *dest, const void *src, size_t n);

#endif /* MEM_H */
