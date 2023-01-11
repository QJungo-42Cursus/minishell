/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:26:53 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/22 17:21:07 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "t_word.h"
#include "../../libft.h"
#include "conversions/conversions.h"
#include "writer/writer.h"
#include "utils/utils.h"

int	ft_printf(const char *string, ...)
{
	va_list	args;
	t_list	*words;
	int		word_count;
	int		n_char;

	if (string == NULL)
		return (-1);
	word_count = index_w(string, &words);
	if (word_count == 0)
		return (0);
	va_start(args, string);
	n_char = writer(words, args, string);
	ft_lstclear(&words, free);
	va_end(args);
	return (n_char);
}

//
// 
// ############# SPRINTF ###############
//
//
static char	*all_in_string(int final_len, t_list **words)
{
	char	*res;
	int		count;
	int		total;
	t_list	*list;

	list = *words;
	res = malloc(sizeof(char) * (final_len + 1));
	if (res == NULL)
		return (NULL);
	count = 0;
	total = 0;
	while (list != NULL)
	{
		count = ft_strlen((const char *)((t_word *)list->content)->string);
		ft_strlcpy(&res[total],
			(const char *)((t_word *)list->content)->string, count + 1);
		total += count;
		free((char *)((t_word *)list->content)->string);
		list = list->next;
	}
	res[final_len] = '\0';
	return (res);
}

char	*ft_sprintf(const char *string, ...)
{
	va_list	args;
	t_list	*words;
	int		word_count;
	int		n_char;
	char	*res;

	if (string == NULL)
		return (NULL);
	word_count = index_w(string, &words);
	if (word_count == 0)
		return (0);
	va_start(args, string);
	n_char = swriter(words, args, string);
	res = all_in_string(n_char, &words);
	ft_lstclear(&words, free);
	va_end(args);
	return (res);
}
