/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:23:49 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 10:16:45 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "../vec/vec.h"

///		taille en x et y de la matrice
///		et un pointeur sur int** -> parceque de toute facon, c'est en 2d
///		{
///			[1, 2, 3],
///			[1, 3, 4],
///			[4, 5, 2]
///		}	 
// TODO change to width
typedef struct s_matrix {
	int		x;
	int		y;
	float	**self;
}	t_matrix;

//			new
t_matrix	new_matrix(float **matrix, int x, int y);
t_matrix	init_matrix(int x, int y);
void		free_matrix(t_matrix matrix);

//			operations
t_matrix	matrix_addition(t_matrix a, t_matrix b);
t_matrix	matrix_product(t_matrix a, t_matrix b);
t_matrix	matrix_product_scal(t_matrix a, float scal);

//			conversions
t_vec2		matrix_to_vec2(t_matrix matrix);
t_vec3		matrix_to_vec3(t_matrix matrix);
t_matrix	vec3_to_matrix(t_vec3 vec);
t_matrix	vec2_to_matrix(t_vec2 vec);

#endif /* MATRIX_H */
