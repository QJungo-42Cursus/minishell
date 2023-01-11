/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:29:24 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/01 13:13:51 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft.h"

int	free_join(char **res, char **to_print, int is_0)
{
	char	*old_res;

	if (!is_0)
	{
		if (*res == NULL || *to_print == NULL)
			return (1);
		old_res = *res;
		*res = ft_strjoin(*res, *to_print);
		if (*res == NULL)
		{
			free(*to_print);
			return (1);
		}
		free(old_res);
		free(*to_print);
	}
	return (0);
}
