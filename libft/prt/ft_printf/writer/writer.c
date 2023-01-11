/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:40:45 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/11 09:30:28 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../t_word.h"
#include "../conversions/conversions.h"
#include "../../../libft.h"
#include "../utils/utils.h"

static int	putstr_res(const char *string)
{
	int	len;

	len = ft_strlen(string);
	return (write(1, string, len));
}

static int	putstr_until(const char *string, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (write(1, &(string[i]), 1) == -1)
			return (-1);
		i++;
	}
	return (0);
}

static int	word(t_word word, int *i_char, const char *string)
{
	int		res;

	res = putstr_until(&(string[word.start]), word.len);
	if (res == -1)
		return (-1);
	(*i_char) += word.len;
	return (0);
}

static int	flag(t_word word, int *i_char, va_list args)
{
	char	*to_print;
	int		res;

	if (word.flag[0] == '%')
	{
		res = putstr_res("%");
		(*i_char)++;
		return (res);
	}
	to_print = conversions(word.flag, args);
	if (to_print == NULL)
		return (-1);
	if (word.flag[0] == 'c' && ft_strlen(to_print) == 0)
	{
		(*i_char)++;
		free(to_print);
		return (putstr_until("", 1));
	}
	res = putstr_res(to_print);
	(*i_char) += ft_strlen(to_print);
	free(to_print);
	return (res);
}

int	writer(const t_list *words, va_list args, const char *string)
{
	int		to_print;
	int		i_word;
	int		i_char;

	i_word = 0;
	i_char = 0;
	while (words != NULL)
	{
		if (((t_word *)words->content)->type == WORD)
		{
			to_print = word(*(t_word *)words->content, &i_char, string);
			if (to_print == -1)
				return (-1);
		}
		else if (((t_word *)words->content)->type == FLAG)
		{
			to_print = flag(*(t_word *)words->content, &i_char, args);
			if (to_print == -1)
				return (-1);
		}
		words = words->next;
		i_word++;
	}
	return (i_char);
}
