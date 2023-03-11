/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 21:22:48 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/20 19:03:34 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "char/char.h"
# include "prt/prt.h"
# include "lst/lst.h"
# include "nb/nb.h"
# include "mem/mem.h"
# include "str/str.h"

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

#define STR (char *)

#endif
