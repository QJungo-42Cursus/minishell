#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_minishell {
	//char	*prompt;  // avoir un truc constant + le path qui change
	//char	*username;

	char	currend_working_directory[4096]; // TODO max ?

	char	**env_paths; // deja parsee
	char	**env_copy; // malloc / pour export et unset

	// last ast ?
}	t_minishell;

#endif /* MINISHELL_H */
