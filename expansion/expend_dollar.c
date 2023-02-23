/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:45 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:02:51 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "expansion.h"
#include "../env/env.h"

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
			var_value = ft_strdup((char *)"");
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

char	*expand_dollar(const char *token,
			t_minishell *minishell, t_position position)
{
	char	*var_value;
	char	*a;
	char	*new_token;
	char	*b;

	var_value = get_var_value(token, minishell, position);
	if (var_value == NULL)
		return (NULL);
	if (set_sides(token, position, &a, &b) == ERROR)
	{
		free(var_value);
		return (NULL);
	}
	new_token = ft_sprintf("%s%s%s", a, var_value, b);
	free(a);
	free(b);
	free(var_value);
	return (new_token);
}
