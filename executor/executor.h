#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../parser/parser.h"
# include "../minishell.h"

// utils
int			fork1();
int			pipe_index(int i, int read);
void		close_all_pipes(int *fds, int pipe_count);
void		replace_argv0_with_full_path(t_cmd *cmd, t_minishell *minishell);

// executor.c
int			execute(t_cmd *cmd, t_minishell *minishell);
int         execute_builtin(t_cmd *cmd, t_minishell *minishell, int *exit_status);

// execute_pipeline.c
int			execute_pipeline(t_cmd *pipeline_cmd, t_minishell *minishell);

#endif /* EXECUTOR_H */
