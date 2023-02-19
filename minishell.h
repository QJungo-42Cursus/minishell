#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX_PATH_LEN 4096

typedef struct s_minishell {
	char	*prompt_msg;// avoir un truc constant + le path qui change
	//char	*username;
	char	current_working_directory[MAX_PATH_LEN];
	char	**env_paths; // deja parsee
	char	**env_copy; // malloc / pour export et unset
	char	*cmd_input;
	int		last_exit_status;
	int		should_exit;
}	t_minishell;

typedef struct s_position
{
	int start;	// inclusif
	int end;	// exclusif
}	t_position;

int     init_minishell(t_minishell *minishell, char **envp);
int     refresh_prompt(t_minishell *minishell);

#endif /* MINISHELL_H */
