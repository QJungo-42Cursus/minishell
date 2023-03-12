/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:42 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/12 15:10:10 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include "../env/env.h"
#include <stdlib.h>
#include <stdio.h>
#include "expansion.h"

static char	*get_var_value(const char *token,
		t_minishell *minishell, t_position position)
{
	char		*var_name;
	char		*var_value;

	var_name
		= ft_substr(token, position.start + 1, position.end - position.start);
	if (var_name == NULL)
		return (NULL);
	if (ft_strncmp(var_name, "?", 2) == 0)
		var_value = ft_itoa(minishell->last_exit_status);
	else
	{
		if (get_env_var_index((const char **)minishell->env_copy,
				var_name) == -1)
			var_value = NULL;
		else
			var_value = get_env_var_value(var_name,
					(const char **)minishell->env_copy);
	}
	free(var_name);
	return (var_value);
}

static int	set_sides(const char *token,
		t_position position, char **a, char **b)
{
	if (position.start == 0)
		*a = ft_strdup((char *)"");
	else
		*a = ft_substr(token, 0, position.start);
	if (a == NULL)
		return (ERROR);
	*b = ft_substr(token, position.end + 1, ft_strlen(token) - position.end);
	if (b == NULL)
	{
		free(*a);
		return (ERROR);
	}
	return (SUCCESS);
}

static char	*expand_dollar(char *token,
			t_minishell *minishell, t_position position)
{
	char	*var_value;
	char	*a;
	char	*new_token;
	char	*b;

	var_value = get_var_value(token, minishell, position);
	if (position.start == 0 && position.end == ft_strlen(token) - 1)
		return (var_value);
	if (set_sides(token, position, &a, &b) == ERROR)
	{
		if (var_value != NULL)
			free(var_value);
		return (NULL);
	}
	if (var_value == NULL)
		new_token = ft_sprintf("%s%s", a, b);
	else
		new_token = ft_sprintf("%s%s%s", a, var_value, b);
	free(a);
	free(b);
	if (var_value != NULL)
		free(var_value);
	return (new_token);
}

void	expand(char **token, t_minishell *minishell)
{
	t_position	index;
	char		*new_token;

	if (get_var_position(0, *token, &index.start, &index.end) == FALSE)
		return ;
	new_token = expand_dollar(*token, minishell, index);
	free(*token);
	*token = new_token;
	if (new_token != NULL)
		expand(token, minishell);
	if (*token == NULL)
	{
		*token = ft_strdup((char *)"");
		return ;
	}
	expand(token, minishell);
}
