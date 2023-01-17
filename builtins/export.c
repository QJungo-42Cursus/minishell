/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 21:18:52 by agonelle          #+#    #+#             */
/*   Updated: 2023/01/17 21:30:47 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"

int	add_env_var(t_minishell *mini, char *var)
{
	char	**new_env_copy;
	int		i;

	i = 0;
	while (mini->env_copy[i] != NULL)
		i++;
	new_env_copy = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (mini->env_copy[i] != NULL)
	{
		new_env_copy[i] = mini->env_copy[i];
		i++;
	}
	new_env_copy[i] = var;
	new_env_copy[i + 1] = NULL;
	return (SUCCESS);
}

int	export(t_minishell *minishell, char **args)
{
	char	*var;

	var = ft_strdup(args[1]);
	if (!var)
		return (ERROR);
	if (add_env_var(minishell, var) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
