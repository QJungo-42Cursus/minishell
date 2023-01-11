/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_sprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:44:13 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/22 14:44:15 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	test_sprintf(void)
{
	long	l;
	char	*test;

	l = (long)INT_MAX + 1;
	test = NULL;
	test = ft_sprintf("sans flag");
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("INT : %d\n", -50);
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("UNSIGNED : %u\n", -50);
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("POINTER : %p\n", "");
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("STRING : %s\n", "'salut !'");
	printf("%s\n", test);
	free(test);
	test = ft_sprintf("%% %%", "'salut !'");
	printf("%s\n", test);
	free(test);
}
