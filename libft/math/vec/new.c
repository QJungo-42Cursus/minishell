/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:35:34 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:52:08 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_math.h"

t_vec2	new_vec2(float x, float y)
{
	t_vec2	n;

	n.x = x;
	n.y = y;
	return (n);
}

t_vec3	new_vec3(float x, float y, float z)
{
	t_vec3	n;

	n.x = x;
	n.y = y;
	n.z = z;
	return (n);
}
