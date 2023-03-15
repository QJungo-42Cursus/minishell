/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:48 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/15 11:08:48 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	get_var_position(int begin_from, const char *token, t_position *index);

typedef struct s_quootes {
	t_bool	quoted;
	t_bool	dquoted;
} t_quootes;

static int	_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

static int	_isalnum(char c)
{
	return (_isalpha(c) || (c >= '0' && c <= '9'));
}

#include <stdio.h>
int go_to_next_quote(int index, t_quootes q, const char *token)
{
	char	sep;
	int		i;

	if (q.dquoted)
		sep = '"';
	else if (q.quoted)
		sep = '\'';
	else
		sep = '\'';
	i = index - 1;
	while (token[i] != '\0' && token[i] != sep)
		i++;
	//printf("send from : %s\n", &token[i]);
	return (i + 1);
}

static int	var_founded(int i, t_position *index,
		const char *token, t_quootes q)
{
	if (token[i] == '?')
	{
		index->start = i - 1;
		index->end = i;
		return (TRUE);
	}
	if (token[i] == '\0')
		return (FALSE);
	// === 
	if (_isalpha(token[i]) == FALSE)
	{
		(void)q;
		if (q.dquoted || q.quoted)
		{
			//printf("YYYYYY (quoted) %s\n", &token[i]);
			return (get_var_position(go_to_next_quote(i, q, token), token, index));
		}
		return (get_var_position(i, token, index));
	}
	// === TODO attention recursion !
	index->start = i - 1;
	while (token[i] != '\0'
		&& _isalnum(token[i])
		&& !is_in_charset(token[i], "$:\'\" "))
		i++;
	index->end = i - 1;
	if (index->start == index->end)
		return (FALSE);
	return (TRUE);
}

int	get_var_position(int begin_from, const char *token, t_position *index)
{
	int			i;
	t_quootes	q;

	q.quoted = FALSE;
	q.dquoted = FALSE;
	i = begin_from;
	if (ft_strlen(token) == 0)
		return (FALSE);
	while (token[i] != '\0')
	{
		if (token[i] == '"' && q.quoted == FALSE)
			q.dquoted = !q.dquoted;
		else if (token[i] == '\'' && q.dquoted == FALSE)
			q.quoted = !q.quoted;
		else if (token[i] == '$' && q.quoted == FALSE)
			return (var_founded(i + 1, index, token, q));
		i++;
	}
	return (FALSE);
}
