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

void	append_to_free_list(t_minishell *minishell, t_list *to_append)
{
	int		lst_size;
	void	**new_free_list;

	lst_size = 0;
	while (minishell->tokens_to_free[lst_size] != NULL)
		lst_size++;
	new_free_list = malloc(sizeof(void *) * (lst_size + 2));
	if (new_free_list == NULL)
		malloc_error(minishell);
	lst_size = 0;
	while (minishell->tokens_to_free[lst_size] != NULL)
	{
		new_free_list[lst_size] = minishell->tokens_to_free[lst_size];
		lst_size++;
	}
	new_free_list[lst_size] = to_append;
	new_free_list[lst_size + 1] = NULL;
	free(minishell->tokens_to_free);
	minishell->tokens_to_free = new_free_list;
}
