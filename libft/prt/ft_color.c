/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:11:46 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/08 11:13:20 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prt.h"

void	ft_color(t_color color, int font)
{
	if (color == RESET)
		ft_printf("\033[0m");
	if (color == RED)
		ft_printf("\033[0;31m");
	if (color == GREEN)
		ft_printf("\033[0;32m");
	if (color == YELLOW)
		ft_printf("\033[0;33m");
	if (color == BLUE)
		ft_printf("\033[0;34m");
	if (color == PURPLE)
		ft_printf("\033[0;35m");
	if (color == CYAN)
		ft_printf("\033[0;36m");
	if (color == WHITE)
		ft_printf("\033[0;37m");
	if (font == BOLD)
		ft_printf("\033[1m");
}
