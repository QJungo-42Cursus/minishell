/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prt.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:39:08 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/11 09:52:20 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRT_H
# define PRT_H

typedef enum e_color {
	BLUE,
	RED,
	YELLOW,
	PURPLE,
	GREEN,
	CYAN,
	WHITE,
	RESET,
	BOLD,
	STD,
}	t_color;

int		ft_printf(const char *string, ...);
char	*ft_sprintf(const char *string, ...);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_color(t_color color, int font);

#endif /* PRT_H */
