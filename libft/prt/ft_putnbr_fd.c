/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:52:28 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:10:28 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	exeptions(int n, int fd)
{
	if (n == 0)
		ft_putstr_fd("0", fd);
	if (n == INT_MIN)
		ft_putstr_fd("-2147483648", fd);
	if (n == INT_MIN || n == 0)
		return (1);
	return (0);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	ten_factor;
	unsigned int	to_add;
	int				flag;

	if (exeptions(n, fd))
		return ;
	ten_factor = 1000000000;
	flag = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	while (ten_factor)
	{
		to_add = n / ten_factor;
		if (to_add || flag)
		{
			flag = 1;
			ft_putchar_fd(to_add + 48, fd);
		}
		n -= to_add * ten_factor;
		ten_factor /= 10;
	}
}
