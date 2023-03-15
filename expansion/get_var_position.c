/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:48 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/14 17:48:19 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
int	get_var_position(int begin_from, const char *token,
		int *start_index, int *end_index);

static int	_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

static int	_isalnum(char c)
{
	return (_isalpha(c) || (c >= '0' && c <= '9'));
}

static int	var_founded(int i, int *start_index,
		int *end_index, const char *token)
{
	if (token[i] == '?')
	{
		*start_index = i - 1;
		*end_index = i;
		return (TRUE);
	}
	if (token[i] == '\0')
		return (FALSE);
	// === 
	if (_isalpha(token[i]) == FALSE)
		return get_var_position(i, token, start_index, end_index);
	// === TODO attention recursion !
	*start_index = i - 1;
	while (token[i] != '\0'
		&& _isalnum(token[i])
		&& !is_in_charset(token[i], "$:\'\" "))
		i++;
	*end_index = i - 1;
	if (*start_index == *end_index)
		return (FALSE);
	return (TRUE);
}

int	get_var_position(int begin_from, const char *token,
		int *start_index, int *end_index)
{
	int		quoted;
	int		dquoted;
	int		i;

	quoted = FALSE;
	dquoted = FALSE;
	i = begin_from;
	if (ft_strlen(token) == 0)
		return (FALSE);
	while (token[i] != '\0')
	{
		if (token[i] == '"' && quoted == FALSE)
			dquoted = !dquoted;
		else if (token[i] == '\'' && dquoted == FALSE)
			quoted = !quoted;
		else if (token[i] == '$' && quoted == FALSE)
			return (var_founded(i + 1, start_index, end_index, token));
		i++;
	}
	return (FALSE);
}
