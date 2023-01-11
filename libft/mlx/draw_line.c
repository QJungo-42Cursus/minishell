/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 08:40:53 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/10 15:19:48 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_mlx.h"
#include "../libft.h"

static void	move(t_vec2 *moving_pixel,
	t_line line, t_bool little, t_bool y_dist_greater)
{
	int		xm;
	int		ym;

	xm = 1;
	ym = 1;
	if (line.a.x > line.b.x)
		xm = -1;
	if (line.a.y > line.b.y)
		ym = -1;
	if (little)
	{
		if (y_dist_greater)
			moving_pixel->x += xm;
		else
			moving_pixel->y += ym;
	}
	else
	{
		if (y_dist_greater)
			moving_pixel->y += ym;
		else
			moving_pixel->x += xm;
	}
}

// TODO add gradient
static void	loop(t_line line, t_img_data *img, t_vec2 dist, float speed)
{
	float	cursor;
	float	color_speed;

	color_speed = ft_fabs(ft_fabs(line.color.start) - ft_fabs(line.color.end));
	(void)color_speed;
	cursor = 0;
	while (1)
	{
		if (check_max(line.a.x, line.a.y, *img))
			break ;
		pixel_to_image(img, line.a, line.color.start);
		move(&line.a, line, FALSE, dist.y > dist.x);
		cursor += 1;
		if (cursor >= speed)
		{
			move(&line.a, line, TRUE, dist.y > dist.x);
			cursor -= speed;
		}
		if (assert_rounded_vec2(line.a, line.b))
			break ;
	}
}

static void	straight_loop(t_vec2 moving_pixel, t_line line, t_img_data *img)
{
	int		move_factor;

	move_factor = 1;
	if (round(line.a.y) == round(line.b.y) && (line.a.x > line.b.x))
		move_factor = -1;
	if (round(line.a.x) == round(line.b.x) && (line.a.y > line.b.y))
		move_factor = -1;
	while (1)
	{
		if (round(line.a.y) == round(line.b.y))
			moving_pixel.x += move_factor;
		else
			moving_pixel.y += move_factor;
		if (round(moving_pixel.x) == round(line.b.x)
			&& round(moving_pixel.y) == round(line.b.y))
			break ;
		if (check_max(moving_pixel.x, moving_pixel.y, *img))
			break ;
		pixel_to_image(img, moving_pixel, line.color.start);
	}
}

void	draw_line(t_img_data *img, t_line line)
{
	t_droite	droite;
	float		speed;
	t_vec2		dist;

	if (round(line.a.x) == round(line.b.x)
		|| round(line.a.y) == round(line.b.y))
		return (straight_loop(new_vec2(line.a.x, line.a.y), line, img));
	droite.m = slope(line.a, line.b);
	droite.b = ordonnate_to_origin(line.a.x, line.a.y, droite.m);
	offset(new_vec2(img->size.x, img->size.y), &line.a, droite);
	offset(new_vec2(img->size.x, img->size.y), &line.b, droite);
	dist = new_vec2(ft_fabs(ft_fabs(line.a.x) - ft_fabs(line.b.x)),
			ft_fabs(ft_fabs(line.a.y) - ft_fabs(line.b.y)));
	speed = dist.y / dist.x;
	if (dist.x > dist.y)
		speed = dist.x / dist.y;
	loop(line, img, dist, speed);
}
