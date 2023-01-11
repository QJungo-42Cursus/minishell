/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:35:13 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 10:20:01 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../vec/vec.h"

float	slope(t_vec2 a, t_vec2 b)
{
	float	m;

	m = (b.y - a.y) / (b.x - a.x);
	return (m);
}

float	ordonnate_to_origin(float x, float y, float m)
{
	float	b;

	if (isinf(m))
		return (x);
	b = y - m * x;
	if (isnan(b))
		b = 0;
	return (b);
}

// Grace au théorème de Pythagore,
// on peut calculer la distance entre deux points
float	distance(t_vec2 a, t_vec2 b)
{
	return (sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2)));
}

t_vec2	pos_from_distance(t_vec2 a, float distance, float angle)
{
	t_vec2	b;

	b.x = a.x + distance * cos(angle);
	b.y = a.y + distance * sin(angle);
	return (b);
}
