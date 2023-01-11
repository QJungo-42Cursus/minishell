/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:35:34 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 15:25:17 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "vec.h"

t_vec3	*copy_vec3_list(t_vec3 *src, int size)
{
	t_vec3	*dst;
	int		i;

	dst = malloc(sizeof(t_vec3) * size);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

t_vec2	*copy_vec2_list(t_vec2 *src, int size)
{
	t_vec2	*dst;
	int		i;

	dst = malloc(sizeof(t_vec3) * size);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

void	copy_vec3_list_to2(t_vec3 *src, int size, t_vec2 *dst)
{
	int		i;

	i = 0;
	while (i < size)
	{
		dst[i] = vec3_to2(src[i]);
		i++;
	}
}
