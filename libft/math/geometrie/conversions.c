/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 10:21:08 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 10:24:10 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180);
}

float	rad_to_deg(float rad)
{
	return (rad * 180 / M_PI);
}
