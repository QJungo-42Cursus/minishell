#include "libft/libft.h"       // ...
#include <stdio.h>             // ...
#include <stdlib.h>            // ...
#include <unistd.h>            // ...
#include <readline/history.h>  // readline history
#include <readline/readline.h> // readline lib

#include "fcntl.h"
#include "libft/libft.h"
#include "sys/wait.h"
#include "tokenizer/tokenizer.h"

#include "tests/debug_helper.h"

typedef struct s_term {
	char	*usr;
	char	*prompt;
	char	*cwd;
	char	**paths;
}	t_term;

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

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_input;
	char	*prompt_msg;

	(void) argc;
	(void) argv;
	(void) envp;
	prompt_msg = ft_strdup("minishell $>");
	while (1)
	{
		cmd_input = readline(prompt_msg);
		if (check_input(cmd_input))
		{
			printf("'%s' can't be handle, since we are not doing much (for now).\n", cmd_input);
			free(cmd_input);
		}
		else
		{
			free(cmd_input);
			return (0);
		}
	}
}
