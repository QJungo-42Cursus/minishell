/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:31:50 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 14:11:56 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "matrix.h"

t_matrix	vec2_to_matrix(t_vec2 vec)
{
	float		**matrix;
	t_matrix	n;

	matrix = (float **)malloc(sizeof(float *) * 2);
	matrix[0] = (float *)malloc(sizeof(float) * 1);
	matrix[1] = (float *)malloc(sizeof(float) * 1);
	matrix[0][0] = vec.x;
	matrix[1][0] = vec.y;
	n = new_matrix(matrix, 1, 2);
	return (n);
}

t_matrix	vec3_to_matrix(t_vec3 vec)
{
	float		**matrix;
	t_matrix	n;

	matrix = (float **)malloc(sizeof(float *) * 3);
	matrix[0] = (float *)malloc(sizeof(float) * 1);
	matrix[1] = (float *)malloc(sizeof(float) * 1);
	matrix[2] = (float *)malloc(sizeof(float) * 1);
	matrix[0][0] = vec.x;
	matrix[1][0] = vec.y;
	matrix[2][0] = vec.z;
	n = new_matrix(matrix, 1, 3);
	return (n);
}

t_vec3	matrix_to_vec3(t_matrix matrix)
{
	t_vec3		vec;

	vec.x = matrix.self[0][0];
	vec.y = matrix.self[1][0];
	vec.z = matrix.self[2][0];
	return (vec);
}

t_vec2	matrix_to_vec2(t_matrix matrix)
{
	t_vec2		vec;

	vec.x = matrix.self[0][0];
	vec.y = matrix.self[1][0];
	return (vec);
}
