/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:10:28 by agonelle          #+#    #+#             */
/*   Updated: 2023/03/14 17:12:07 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	list_len(char **list)
{
	int		i;

	i = 0;
	while (list[i] != NULL)
		i++;
	return (i);
}

int	add_env_var(t_minishell *mini, char *var)
{
	char	**new_env_copy;
	int		i;

	new_env_copy
		= (char **)malloc(sizeof(char *) * (list_len(mini->env_copy) + 2));
	if (new_env_copy == NULL)
		return (ERROR);
	i = 0;
	while (mini->env_copy[i])
	{
		new_env_copy[i] = mini->env_copy[i];
		i++;
	}
	new_env_copy[i] = var;
	new_env_copy[i + 1] = NULL;
	free(mini->env_copy);
	mini->env_copy = new_env_copy;
	return (SUCCESS);
}
