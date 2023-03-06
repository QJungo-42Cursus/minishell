/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:30 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/06 10:27:00 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define QUOTE '\''
#define DQUOTE '"'

void	unquote(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == QUOTE || str[i] == DQUOTE)
			i++;
		if (str[i] == '\0')
			break ;
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}
