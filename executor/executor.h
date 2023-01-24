#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../parser/parser.h"

// utils
int			fork1();
int			pipe_index(int i, int read);
void		close_all_pipes(int *fds, int pipe_count);

// execute.c
int	execute(t_cmd *cmd);

#endif /* EXECUTOR_H */
