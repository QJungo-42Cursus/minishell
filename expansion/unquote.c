/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:30 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/06 19:08:38 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <stdio.h>

void	iunquote(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("before: |%s|\n", str);
	while (str[i] != '\0')
	{
		printf("%d -> %c \t\t", i, str[i]);
		if (is_in_charset(str[i], "\'\""))
			i++;
		if (str[i] == '\0')
			break ;
		str[j] = str[i];
		printf("%d -> %c \n", i, str[i]);
		i++;
		j++;
	}
	str[j] = '\0';
	printf("unquoted: |%s|\n\n", str);
}


char	set_sep(char c)
{
	if (is_in_charset(c, "\'\""))
	{
		printf("ptn de sep |%c|\n", c);
		return (c);
	}
	return (0);
}

t_bool	move_cursor(int *i, int *j, char *str, char *sep)
{
	while (str[*i] != '\0' && !is_in_charset(str[*i], "\'\""))
	{
		(*i)++;
		(*j)++;
	}
	if (ft_strlen(str) == *i)
		return ((t_bool)TRUE);
	if (str[*i] == str[(*i) + 1])
	{
		ft_memmove(&str[(*i) + 2], str[*i], ft_strlen(str[*i]);
	}


	*sep = set_sep(str[*i]);

	return ((t_bool)FALSE);
}

void	unquote(char *str)
{
	int		i;
	int		j;
	char	sep;
	t_bool	is_in;

	i = 0;
	j = 0;
	if (move_cursor(&i, &j, str, &sep))
		return ;
	is_in = TRUE;
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == sep && is_in)
		{
			printf("in\n\n");
			is_in = FALSE;
			unquote(&str[i]);
		}
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
	printf("unquoted: |%s|\n\n", str);
}
