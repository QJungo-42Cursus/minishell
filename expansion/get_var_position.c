/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:48 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/06 14:00:17 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

static int	var_founded(int i, int *start_index,
		int *end_index, const char *token)
{
	*start_index = i;
	if (token[i] != '\0')
		i++;
	while (token[i] != '\0' && is_in_charset(token[i], "$:\'\" ") == FALSE)
		i++;
	*end_index = i - 1;
	return (TRUE);
}

int	get_var_position(int begin_from, const char *token,
		int *start_index, int *end_index)
{
	int		quoted;
	int		i;

	quoted = FALSE;
	i = begin_from;
	if (ft_strlen(token) == 0)
		return (FALSE);
	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			quoted = !quoted;
		if (token[i] == '$' && !quoted)
			return (var_founded(i, start_index, end_index, token));
		i++;
	}
	return (FALSE);
}
