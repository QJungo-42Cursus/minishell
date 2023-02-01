#ifndef BUILTINS_H
# define BUILTINS_H
# include "../minishell.h"

int		echo(char **argv);
int		cd(t_minishell *minishell, char **argv);
int		pwd(t_minishell *minishell, char **argv);
int		env(t_minishell *minishell, char **argv);
int		export_(t_minishell *minishell, char **argv);
int		unset(t_minishell *minishell, char **argv);
int		exit_(t_minishell *minishell, char **argv, int exit_status);

#endif /* BUILTINS_H */
