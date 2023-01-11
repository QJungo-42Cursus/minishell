/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:17:02 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 16:03:03 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../vec/vec.h"
#include "../ft_math.h"

t_vec3	rotation_x(t_vec3 point, float angle)
{
	t_vec3		b;

	b.x = point.x;
	b.y = point.y * cos(angle) + point.z * sin(angle);
	b.z = point.y * -sin(angle) + point.z * cos(angle);
	return (b);
}

t_vec3	rotation_z(t_vec3 a, float angle)
{
	t_vec3	b;

	b.x = a.x * -cos(angle) + a.y * sin(angle);
	b.y = a.x * sin(angle) + a.y * cos(angle);
	b.z = a.z;
	return (b);
}

void	rotation_3d(t_vec3 *points, int length, float angle, char axe)
{
	int		i;

	angle = deg_to_rad(angle);
	i = 0;
	while (i < length)
	{
		if (axe == 'z')
			points[i] = rotation_z(points[i], angle);
		if (axe == 'x')
			points[i] = rotation_x(points[i], angle);
		i++;
	}
}

//	TODO a sa place ici ?
void	map_scale(t_vec2 *points, int length, float scale)
{
	int	i;

	i = 0;
	while (i < length)
	{
		points[i].x *= scale;
		points[i].y *= scale;
		i++;
	}
}
