/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 11:18:38 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/11 17:42:31 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../tokenizer/tokenizer.h"

// 1. trouver le debut (" ou ')
// 2. trouver la fin
// 3. memmove
// 4. recursivite
void	unquote(char *str)
{
	int			i;
	t_position	pos;
	char		sep;

	i = 0;
	while (str[i] != '\0' && !is_in_charset(str[i], "\'\""))
		i++;
	if (str[i] == '\0')
		return ;
	sep = str[i];
	pos.start = i;
	i++;
	while (str[i] != '\0' && str[i] != sep)
		i++;
	if (str[i] == '\0')
		return ;
	ft_memmove(&str[pos.start], &str[pos.start + 1],
		ft_strlen(&str[pos.start + 1]) + 1);
	pos.end = i - 1;
	ft_memmove(&str[pos.end], &str[pos.end + 1],
		ft_strlen(&str[pos.end + 1]) + 1);
	unquote(&str[pos.end]);
}
