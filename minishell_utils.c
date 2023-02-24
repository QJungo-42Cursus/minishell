/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:01:40 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 16:45:42 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include "env/env.h"
#include "builtins/builtins.h"

void	refresh_prompt(t_minishell *minishell)
{
	if (minishell->prompt_msg != NULL)
		free(minishell->prompt_msg);
	minishell->prompt_msg = ft_sprintf("[msh %s]$ ",
			minishell->current_working_directory);
	if (minishell->prompt_msg == NULL)
		malloc_error(minishell);
}

int	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->last_exit_status = 0;
	minishell->prompt_msg = NULL;
	if (getcwd(minishell->current_working_directory, MAX_PATH_LEN + 1) == NULL)
	{
		perror("minishell: getcwd: ");
		return (ERROR);
	}
	minishell->env_copy = cpy_envp(envp);
	if (minishell->env_copy == NULL)
	{
		perror("minishell: cpy_envp: ");
		return (ERROR);
	}
	refresh_prompt(minishell);
	if (minishell->prompt_msg == NULL)
	{
		split_free(minishell->env_copy);
		perror("minishell: refresh_prompt: ");
		return (ERROR);
	}
	minishell->should_exit = FALSE;
	return (SUCCESS);
}

void	malloc_error(t_minishell *minishell)
{
	perror("malloc");
	free_ast(minishell->current_ast);
	exit_(minishell, NULL, 1);
}
