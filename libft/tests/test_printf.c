/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:43:17 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/22 14:43:42 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	test_printf(void)
{
	long	l;

	l = (long)INT_MAX + 1;
	ft_printf("INT : %d\n", -50);
	ft_printf("UNSIGNED : %u\n", -50);
	ft_printf("POINTER : %p\n", "");
	ft_printf("STRING : %s\n", "'salut !'");
}
/*
	// TODO le float coupe tout ce qu'il a apres le %f...
	ft_printf("FLOAT : %f yaa \n", 10.1f);
	// TODO ne fonctionne tout simplement pas...
	ft_printf("LONG: %ld\n", l);
*/
