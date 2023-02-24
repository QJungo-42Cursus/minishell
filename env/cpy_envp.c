/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:18:13 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:19:07 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"

static char	**free_fail(char **env_copy, int i)
{
	while (i >= 0)
		free(env_copy[i--]);
	free(env_copy);
	return (NULL);
}

// malloc OK !
char	**cpy_envp(char **envp)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (envp[i])
		i++;
	env_copy = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (env_copy[i] == NULL)
			return (free_fail(env_copy, i - 1));
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}
