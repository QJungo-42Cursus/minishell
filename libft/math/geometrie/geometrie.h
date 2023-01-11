/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometrie.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:18:04 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 22:07:29 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRIE_H
# define GEOMETRIE_H

# include "../vec/vec.h"

//			line
float		slope(t_vec2 a, t_vec2 b);
float		ordonnate_to_origin(float x, float y, float m);
float		distance(t_vec2 a, t_vec2 b);
t_vec2		pos_from_distance(t_vec2 a, float distance, float angle);

//			convertion
float		deg_to_rad(float deg);
float		rad_to_deg(float rad);

//			operations sur des listes de points
void		rotation_3d(t_vec3 *points, int length, float angle, char axe);
void		map_scale(t_vec2 *points, int length, float scale);

//			translation (mouvment)
void		translation_2d(t_vec2 *vertices, int length, t_vec2 vec);
void		translation_3d(t_vec3 *vertices, int length, t_vec3 vec);

#endif /* GEOMETRIE_H */
