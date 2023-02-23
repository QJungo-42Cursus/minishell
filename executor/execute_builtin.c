/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:20:26 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:20:27 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "../builtins/builtins.h"

int	execute_builtin(t_cmd *cmd, t_minishell *minishell, int *exit_status)
{
	char	*cmd_name;

	cmd_name = cmd->s_command.argv[0];
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		*exit_status = echo(cmd->s_command.argv);
	else if (ft_strncmp(cmd_name, "cd", 3) == 0)
		*exit_status = cd(minishell, cmd->s_command.argv);
	else if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		*exit_status = pwd(minishell, cmd->s_command.argv);
	else if (ft_strncmp(cmd_name, "export", 7) == 0)
		*exit_status = export_(minishell, cmd->s_command.argv);
	else if (ft_strncmp(cmd_name, "unset", 6) == 0)
		*exit_status = unset(minishell, cmd->s_command.argv);
	else if (ft_strncmp(cmd_name, "env", 4) == 0)
		*exit_status = env(minishell, cmd->s_command.argv);
	else if (ft_strncmp(cmd_name, "exit", 5) == 0)
		*exit_status = exit_(minishell, cmd->s_command.argv, SUCCESS);
	else
		return (FALSE);
	return (TRUE);
}
