/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:44:04 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/22 14:47:20 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../t_word.h"
#include "../../../libft.h"

static void	set_flag(
		t_word *word, int *i_char, const char *string)
{
	int	i_flag;

	(*i_char)++;
	word->type = FLAG;
	i_flag = 0;
	if (string[(*i_char)] == '%')
	{
		word->flag[0] = '%';
		word->flag[1] = '\0';
		(*i_char)++;
		return ;
	}
	while (!is_in_charset(string[(*i_char)], "cspdiuxX"))
	{
		if (string[(*i_char)] == '%')
			return ;
		word->flag[i_flag] = string[*i_char];
		i_flag++;
		(*i_char)++;
	}
	word->flag[i_flag] = string[*i_char];
	word->flag[i_flag + 1] = '\0';
	(*i_char)++;
}

static void	set_word(
		t_word *word, int *i_char, const char *string)
{
	word->type = WORD;
	while (string[*i_char] != '%' && string[*i_char] != '\0')
		(*i_char)++;
	word->len = (*i_char) - word->start;
}

int	index_w(const char *string, t_list **words)
{
	int		i_char;
	int		i_word;
	t_word	*new_word;

	i_char = 0;
	i_word = 0;
	*words = NULL;
	while (string[i_char] != '\0')
	{
		new_word = malloc(sizeof(t_word) * 2);
		new_word->start = i_char;
		if (string[i_char] == '%')
			set_flag(new_word, &i_char, string);
		else
			set_word(new_word, &i_char, string);
		i_word++;
		ft_lstadd_back(words, ft_lstnew(new_word));
	}
	return (i_word);
}
