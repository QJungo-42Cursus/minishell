/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:31:50 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 10:15:23 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "matrix.h"

float	op(t_matrix a, t_matrix b, int x, int y)
{
	int		i;
	float	res;

	i = 0;
	res = 0;
	while (i < a.x)
	{
		res += a.self[y][i] * b.self[i][x];
		i++;
	}
	return (res);
}

// produit de matrice
t_matrix	matrix_product(t_matrix a, t_matrix b)
{
	t_matrix	n;
	int			x;
	int			y;

	if (a.x != b.y)
		return (new_matrix(NULL, 0, 0));
	n.x = b.x;
	n.y = a.y;
	n.self = malloc(sizeof(float *) * n.y);
	if (n.self == NULL)
		return (n);
	y = 0;
	while (y < n.y)
	{
		n.self[y] = malloc(sizeof(float) * n.x);
		x = 0;
		while (x < n.x)
		{
			n.self[y][x] = op(a, b, x, y);
			x++;
		}
		y++;
	}
	return (n);
}

// element wise matrix multiplication
t_matrix	element_wise_matrix_multiplication(t_matrix a, t_matrix b)
{
	t_matrix	n;
	int			x;
	int			y;

	if (a.x != b.x || a.y != b.y)
		return (new_matrix(NULL, 0, 0));
	n.x = a.x;
	n.y = a.y;
	n.self = malloc(sizeof(float *) * n.y);
	if (n.self == NULL)
		return (n);
	y = 0;
	while (y < n.y)
	{
		n.self[y] = malloc(sizeof(float) * n.x);
		x = 0;
		while (x < n.x)
		{
			n.self[y][x] = a.self[y][x] * b.self[y][x];
			x++;
		}
		y++;
	}
	return (n);
}

t_matrix	matrix_addition(t_matrix a, t_matrix b)
{
	t_matrix	n;
	int			i;
	int			j;

	if (a.x != b.x || a.y != b.y)
		return (new_matrix(NULL, 0, 0));
	n = new_matrix((float **)malloc(sizeof(float *) * a.y), a.x, a.y);
	i = 0;
	while (i < a.y)
	{
		n.self[i] = (float *)malloc(sizeof(float) * a.x);
		j = 0;
		while (j < a.x)
		{
			n.self[i][j] = a.self[i][j] + b.self[i][j];
			j++;
		}
		i++;
	}
	return (n);
}

// produit de matrice par un scalaire
t_matrix	matrix_product_scal(t_matrix a, float scal)
{
	t_matrix	n;
	int			x;
	int			y;

	n.x = a.x;
	n.y = a.y;
	n.self = malloc(sizeof(float *) * n.y);
	if (n.self == NULL)
		return (n);
	y = 0;
	while (y < n.y)
	{
		n.self[y] = malloc(sizeof(float) * n.x);
		x = 0;
		while (x < n.x)
		{
			n.self[y][x] = a.self[y][x] * scal;
			x++;
		}
		y++;
	}
	return (n);
}
