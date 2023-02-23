/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:20:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:20:23 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../parser/parser.h"
# include "../minishell.h"

// utils
int			fork1(void);
int			pipe_index(int i, int read);
void		close_all_pipes(int *fds, int pipe_count);
void		replace_argv0_with_full_path(t_cmd *cmd, t_minishell *minishell);

// executor.c
int			execute(t_cmd *cmd, t_minishell *minishell);

// execute_x.c
int			execute_pipeline(t_cmd *pipeline_cmd, t_minishell *minishell);
int			execute_redir(t_cmd *cmd, t_minishell *minishell);
int			execute_command(t_cmd *cmd, t_minishell *minishell);
int			execute_builtin(t_cmd *cmd,
				t_minishell *minishell, int *exit_status);

// execute_pipeline_utils.c
void		wait_all(t_cmd *pipeline_cmd, int *exit_status);
int			init_pipes(t_cmd *cmd, int *shitty_pipe);
t_bool		is_last_cmd(t_cmd *pipeline_cmd, int index);
t_bool		has_next_cmd_heredoc(t_cmd *cmd_cursor);

#endif /* EXECUTOR_H */
