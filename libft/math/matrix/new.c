/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:31:50 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 10:15:50 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <stdlib.h>

t_matrix	new_matrix(float **matrix, int x, int y)
{
	t_matrix	n;

	n.self = matrix;
	n.y = y;
	n.x = x;
	return (n);
}

t_matrix	init_matrix(int x, int y)
{
	t_matrix	n;
	int			i;
	int			j;

	n.self = (float **)malloc(sizeof(float *) * y);
	i = 0;
	while (i < y)
	{
		n.self[i] = (float *)malloc(sizeof(float) * x);
		j = 0;
		while (j < x)
		{
			n.self[i][j] = 0;
			j++;
		}
		i++;
	}
	n.y = y;
	n.x = x;
	return (n);
}

void	free_matrix(t_matrix matrix)
{
	int		i;

	i = 0;
	while (i < matrix.y)
	{
		free(matrix.self[i]);
		i++;
	}
	free(matrix.self);
}
