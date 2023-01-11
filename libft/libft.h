/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 21:22:48 by qjungo            #+#    #+#             */
/*   Updated: 2023/01/11 13:57:38 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

/*
# ifdef __cplusplus
#  define _START_CPP extern "C" {
#  define _END_CPP }
# else
#  define _START_CPP
#  define _END_CPP
# endif
*/

# include "math/ft_math.h"
# include "char/char.h"
# include "prt/prt.h"
# include "lst/lst.h"
# include "nb/nb.h"
# include "mem/mem.h"
# include "str/str.h"
# include "mlx/ft_mlx.h"

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif
# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

typedef enum e_bool {
	FALSE,
	TRUE,
	SUCCESS = 0,
	ERROR = 1,
}	t_bool;

char	*get_next_line(int fd);

#endif
