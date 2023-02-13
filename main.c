#include "libft/libft.h"       // ...
#include <stdio.h>             // ...
#include <stdlib.h>            // ...
#include <unistd.h>            // .
#include <signal.h>
#include <errno.h>

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
#include "executor/executor.h"
#include "token_checker/token_checker.h"

static int	check_input_term(char *input)
{
	if (input == NULL)
		return ('0');
	else if (ft_strlen(input) == 0)
		return ('0');
	else if (ft_strncmp(input, "exit", 5) == 0)
	{
		rl_clear_history();
		return ('e');
	}
	else
	{
		add_history(input);
		return (1);
	}
}

static int	main_minishell(t_minishell *minishell, char *valid_input)
{
	t_list	*tokens;
	t_list	*tmp;
	t_cmd	*cmd;

	(void) minishell;
	(void) tmp;
	tokens = tokenizer(valid_input);
	tmp = tokens;
	if (tokens == NULL)
		return (ERROR);
	if (check_valid_tokens(tmp) == ERROR)
	{
		return (ERROR);
	}
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (set_command(tokens, cmd) == ERROR)
		return (ERROR);
	if (execute(cmd, minishell) == 0)
	{
		perror("Command not found");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	main_loop(t_minishell *minishell)
{
	int		cmd_code;

	while (1)
	{
		minishell->cmd_input = readline(minishell->prompt_msg);
		cmd_code = check_input_term(minishell->cmd_input);
		if (cmd_code != 'e')
		{
			if (cmd_code != '0')
			{
				if (main_minishell(minishell, minishell->cmd_input) == ERROR)
					printf("DIE MOTHER FUCKER\n");
				else
					printf("No error\n");
			}
			free(minishell->cmd_input);
		}
		else
		{
			free(minishell->cmd_input);
			free(minishell->prompt_msg);
			return (0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	if (argc != 1)
	{
		errno = EINVAL;
		perror("./minishell error");
		exit (-1);
	}
	(void) argv;
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		errno = EINVAL;
		perror("./minishell error with stream");
		exit (-1);
	}
	if (init_minishell(&minishell, envp) == ERROR)
		return (EXIT_FAILURE);
	main_loop(&minishell);
	/*
	//char **test = ft_split("export CACA=0", ' ');
	//char **cd_test = ft_split("cd /", ' ');
	//char **untest = ft_split("unset LS_COLORS", ' ');
	//export_(&minishell, test);
	//unset(&minishell, untest);
	env(minishell);
	cd(&minishell, cd_test);
	env(minishell);
	*/
	return (0);
}
