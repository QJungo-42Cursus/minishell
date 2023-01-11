/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:40:53 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/09 10:59:32 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ft_mlx.h"
#include "../libft.h"

int	check_max(float x, float y, t_img_data img)
{
	if (x < 0 || y < 0)
		return (1);
	if (x >= img.size.x || y >= img.size.y)
		return (1);
	return (0);
}

void	offset(t_vec2 img_size, t_vec2 *point, t_droite droite)
{
	if (point->x < 0)
	{
		point->x = 0;
		point->y = droite.b;
	}
	if (point->y < 0)
	{
		point->y = 0;
		point->x = point->y / droite.m - droite.b / droite.m;
	}
	if (point->x >= img_size.x)
	{
		point->x = img_size.x - 1;
		point->y = point->x * droite.m + droite.b;
	}
	if (point->y >= img_size.y)
	{
		point->y = img_size.y - 1;
		point->x = point->y / droite.m - droite.b / droite.m;
	}
}
