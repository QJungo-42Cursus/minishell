/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agonelle <agonelle@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 15:08:45 by agonelle          #+#    #+#             */
/*   Updated: 2023/02/19 08:40:47 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"       // ...
#include <errno.h>
#include <stdio.h>
#include <unistd.h>            // .
#include "env/env.h"       // ...

int refresh_prompt(t_minishell *minishell)
{
	if (minishell->prompt_msg != NULL)
		free(minishell->prompt_msg);
	minishell->prompt_msg = ft_strjoin(minishell->current_working_directory,
			" ./minishell $>");
	if (minishell->prompt_msg == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->cmd_input = NULL;
	minishell->last_exit_status = 0;
	minishell->prompt_msg = NULL;
	if (getcwd(minishell->current_working_directory, MAX_PATH_LEN + 1) == NULL)
		return (ERROR);
	minishell->env_copy = cpy_envp(envp);
	if (minishell->env_copy == NULL)
		return (ERROR);
	minishell->env_paths = get_paths_in_env(envp);
	if (minishell->env_paths == NULL)
	{
		split_free(minishell->env_paths);
		return (ERROR);
	}
	refresh_prompt(minishell);
	if (!minishell->prompt_msg)
		return (ERROR);
	minishell->should_exit = FALSE;
	return (SUCCESS);
}
