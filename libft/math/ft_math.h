/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:23:49 by qjungo            #+#    #+#             */
/*   Updated: 2023/01/11 13:57:30 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include "vec/vec.h"
# include "matrix/matrix.h"
# include "geometrie/geometrie.h"

typedef struct s_droite{
	float	m;
	float	b;
	float	x;
	float	y;
	float	move_factor;
}	t_droite;

///		edge (arrete) lie deux sommets qu'on va lier pour dessiner un trait
///		Se base sur l'index du tableau de sommets 
typedef struct s_edge {
	int	a;
	int	b;
}	t_edge;

//			new.c
t_edge		new_edge(int a, int b);

float		ft_fabs(float n);
int			ft_pow(int n, int p);

#endif /* FT_MATH_H */
