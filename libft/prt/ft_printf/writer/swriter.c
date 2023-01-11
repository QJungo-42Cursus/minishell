/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swriter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 08:40:45 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/22 14:47:03 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../t_word.h"
#include "../conversions/conversions.h"
#include "../../../libft.h"
#include "../utils/utils.h"

/*
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
*/

static void	flag(t_word *word, int *i_char, va_list args)
{
	if (word->flag[0] == '%')
	{
		word->string = ft_strdup("%");
		(*i_char)++;
		return ;
	}
	word->string = conversions(word->flag, args);
	if (word->string == NULL)
		return ;
	if (word->flag[0] == 'c' && ft_strlen(word->string) == 0)
	{
		(*i_char)++;
		return ;
	}
	(*i_char) += ft_strlen(word->string);
}

int	swriter(
		const t_list *words,
		va_list args,
		const char *string)
{
	int		i_char;
	t_word	*word;

	i_char = 0;
	while (words != NULL)
	{
		word = (t_word *)words->content;
		if (((t_word *)words->content)->type == WORD)
		{
			word->string = ft_substr(string, word->start, word->len);
			i_char += word->len;
		}
		else if (((t_word *)words->content)->type == FLAG)
			flag((t_word *)words->content, &i_char, args);
		if (word->string == NULL)
			return (-1);
		words = words->next;
	}
	return (i_char);
}
