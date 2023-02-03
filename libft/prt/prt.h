/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:39:08 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/03 11:28:19 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRT_H
# define PRT_H

char	*ft_sprintf(const char *string, ...);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);

#endif /* PRT_H */
