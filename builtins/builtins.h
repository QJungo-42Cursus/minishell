#ifndef BUILTINS_H
# define BUILTINS_H

///	echo est le seul a prendre un flag, le flag -n qui (si j'ai bien compris)
///	n'ajoute plus de retour a la ligne (bash) / ou indique avec un % qu'il n'y en
///	avait pas (zsh)
int		echo(char **argv, char **envp);

int		cd(char *path);
int		pwd(void);
int		env(void);
int		exit(void);
int		export_(char *name, char *value);
int		unset(char *name);

#endif /* BUILTINS_H */
