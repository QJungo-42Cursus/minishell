/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:48:53 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/09 10:12:08 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"
#include <math.h>
///		Add a pixel to an image
///		This is a more optimised way than mlx_put_pixel, because it render
///		only when you put the image to the screen instead of doing 1 by 1

///		Calcul la position de la couleur du pixel dans l'image
///		Set la couleur du pixel au bon endroit (etait transparent avant)
void	pixel_to_image(t_img_data *img, t_vec2 point, int color)
{
	char	*pixel;
	int		offset;

	offset = (int)point.y * img->line_length;
	offset += (int)point.x * (img->bits_per_pixel / 8);
	pixel = img->addr + offset;
	*(unsigned int *)pixel = color;
}
