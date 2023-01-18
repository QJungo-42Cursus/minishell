#ifndef BUILTINS_H
# define BUILTINS_H
# include "../minishell.h"

///	echo est le seul a prendre un flag, le flag -n qui (si j'ai bien compris)
///	n'ajoute plus de retour a la ligne (bash) / ou indique avec un % qu'il n'y en
///	avait pas (zsh)
int		echo(char **argv, char **envp);

int		cd(char *path);
int		pwd(void);
int		env(t_minishell minishell);
int		exit_(void);
int		export_(t_minishell *minishell, char **args);
int		unset(char *name);

#endif /* BUILTINS_H */
