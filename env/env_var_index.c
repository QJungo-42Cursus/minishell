/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_index.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:18:17 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:18:18 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

// TODO const et pas pointeur
int	env_var_index(t_minishell *mini, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = strlen_until(var, "=");
	while (mini->env_copy[i] != NULL)
	{
		if (ft_strncmp(mini->env_copy[i], var, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
