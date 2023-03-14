/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 17:13:06 by agonelle          #+#    #+#             */
/*   Updated: 2023/03/14 17:13:34 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int	print_all_env(t_minishell *minishell)
{
	int		i;

	i = 0;
	while (minishell->env_copy[i] != NULL)
	{
		printf(STR"declare -x %s\n", minishell->env_copy[i]);
		i++;
	}
	return (SUCCESS);
}
