/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:13:07 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 10:17:00 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_math.h"

//		This fonction is used to translate a matrix by a vector
//		and apply the translation on the original matrix
void	translation_3d(t_vec3 *vertices, int length, t_vec3 vec)
{
	int			y;
	t_matrix	translation_matrix;
	t_matrix	new_matrix;

	y = 0;
	while (y < length)
	{
		translation_matrix = vec3_to_matrix(vertices[y]);
		new_matrix = matrix_addition(translation_matrix, vec3_to_matrix(vec));
		vertices[y] = matrix_to_vec3(new_matrix);
		free_matrix(translation_matrix);
		free_matrix(new_matrix);
		y++;
	}
}

void	translation_2d(t_vec2 *vertices, int length, t_vec2 vec)
{
	int			y;
	t_matrix	translation_matrix;
	t_matrix	new_matrix;
	t_matrix	tmp;

	y = 0;
	while (y < length)
	{
		translation_matrix = vec2_to_matrix(vertices[y]);
		tmp = vec2_to_matrix(vec);
		new_matrix = matrix_addition(translation_matrix, tmp);
		vertices[y] = matrix_to_vec2(new_matrix);
		free_matrix(translation_matrix);
		free_matrix(tmp);
		free_matrix(new_matrix);
		y++;
	}
}
