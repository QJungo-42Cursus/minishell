/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:35:26 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/09 10:56:14 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include "../math/ft_math.h"

/// MLX

typedef struct s_mlx {
	void	*self;
	void	*win;
}	t_mlx;

typedef struct s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_vec2	size;
}	t_img_data;

typedef struct s_color_gradient {
	int		n;
	int		start;
	int		end;
}	t_color_gradient;

typedef struct s_line {
	t_vec2				a;
	t_vec2				b;
	t_color_gradient	color;
	int					thickness;
}	t_line;

/// PROTOTYPES

void	draw_line(t_img_data *img, t_line line);
void	pixel_to_image(t_img_data *img, t_vec2 point, int color);
t_line	new_line(t_vec2 a, t_vec2 b, t_color_gradient color, int thickness);
//
void	offset(t_vec2 img_size, t_vec2 *point, t_droite droite);
int		check_max(float x, float y, t_img_data img);

/// EVENT HANDLING

typedef enum e_event_type {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_LEAVE = 8,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	ON_RESIZE = 25,
}	t_event_type;

typedef enum e_key {
	KEY_ESC = 53,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_F = 3,
	KEY_H = 4,
	KEY_G = 5,
	KEY_Z = 6,
	KEY_X = 7,
	KEY_C = 8,
	KEY_V = 9,
	KEY_B = 11,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_E = 14,
	KEY_R = 15,
	KEY_Y = 16,
	KEY_T = 17,
	KEY_ONE = 18,
	KEY_TWO = 19,
	KEY_THREE	= 20,
	KEY_FOUR	= 21,
	KEY_SIX		= 22,
	KEY_FIVE	= 23,
	KEY_NINE	= 25,
	KEY_SEVEN	= 26,
	KEY_EIGHT	= 28,
	KEY_ZERO	= 29,
	KEY_BRACE_R	= 30,
	KEY_O		= 31,
	KEY_U		= 32,
	KEY_BRACE_L	= 33,
	KEY_I		= 34,
	KEY_P		= 35,
	KEY_L		= 37,
	KEY_J		= 38,
	KEY_K		= 40,
	KEY_SEMI	= 41,
	KEY_N		= 45,
	KEY_M		= 46,
	KEY_TAB		= 48,
	KEY_PLUS	= 69,
	KEY_MINUS	= 78,
	KEY_LEFT	= 123,
	KEY_RIGHT	= 124,
	KEY_DOWN	= 125,
	KEY_UP		= 126,
}	t_key;

#endif /* FT_MLX_H */
