#include "libft/libft.h"       // ...
#include <stdio.h>             // ...
#include <stdlib.h>            // ...
#include <unistd.h>            // .
#include <signal.h>
#include <readline/history.h>  // readline history
#include <readline/readline.h> // readline lib
#include "fcntl.h"
#include "sys/wait.h"
// nous
#include "tokenizer/tokenizer.h"
#include "env/env.h"
#include "builtins/builtins.h"
#include "tests/debug_helper.h"
#include "minishell.h"

/*
int	check_input(char *input)
{
	if (input == NULL)
		return (1);
	else if (ft_strlen(input) == 0)
		return (1);
	else if (ft_strncmp(input, "exit", 5) == 0)
	{
		rl_clear_history();
		return (0);
	}
	else
	{
		add_history(input);
		return (1);
	}
}
*/

int main_loop()
{
	char	*cmd_input;
	char	*prompt_msg;

	prompt_msg = ft_strdup("minishell $>");
	while (1)
	{
		cmd_input = readline(prompt_msg);
		/*
		if (check_input(cmd_input))
		{
			printf("'%s' can't be handle, since we are not doing much (for now).\n", cmd_input);
			free(cmd_input);
		}
		*/
		{
			free(cmd_input);
			free(prompt_msg);
			return (0);
		}
	}
}
	
static int	init_minishell(t_minishell *minishell, char **envp)
{
	if (getcwd(minishell->current_working_directory, MAX_PATH_LEN + 1) == NULL)
		return (ERROR);
	minishell->env_copy = cpy_envp(envp);
	if (minishell->env_copy == NULL)
		return (ERROR);
	minishell->env_paths = get_paths_in_env(envp);
	if (minishell->env_paths == NULL)
	{
		split_free(minishell->env_paths);// TODO rename
		return (ERROR);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell minishell;
	(void) argc; (void) argv;
	// TODO balek des args ?
	
	if (init_minishell(&minishell, envp) == ERROR)
		return (EXIT_FAILURE);
	//main_loop();
	
	//char **test = ft_split("export CACA=0", ' ');
	char **cd_test = ft_split("cd /", ' ');
	//char **untest = ft_split("unset LS_COLORS", ' ');
	//export_(&minishell, test);
	//unset(&minishell, untest);
	env(minishell);
	cd(&minishell, cd_test);
	env(minishell);

}
