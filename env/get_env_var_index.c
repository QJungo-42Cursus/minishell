/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var_index.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:18:30 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:18:33 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int	get_env_var_index(const char **env_copy, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = strlen_until(var, "=");
	while (env_copy[i] != NULL)
	{
		if (ft_strncmp(env_copy[i], var, len) == 0 && env_copy[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
