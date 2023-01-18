#ifndef BUILTINS_H
# define BUILTINS_H
# include "../minishell.h"

int		echo(char **argv, char **envp);
int		cd(t_minishell *minishell, char **argv);
int		pwd(void);
int		env(t_minishell minishell);
int		export_(t_minishell *minishell, char **args);
int		unset(t_minishell *minishell, char **args);
//int		exit_(void);

#endif /* BUILTINS_H */
