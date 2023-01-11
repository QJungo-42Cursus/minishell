/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:36:17 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/11 08:59:12 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../../../libft.h"

int	free_join(char **res, char **to_print, int is_0);
int	index_w(const char *string, t_list **words);

#endif /* UTILS_H */
