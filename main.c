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

//int g_should_exit = FALSE;
//

void	handler(int num)
{
	// TODO avec CAT, ne doit pas quitter le shell
	if (num == 2)
		exit(0);
}

enum e_cmd_code {
	NONE = 1,
	EXIT,
};

static int	check_input_term(char *input)
{
	if (input == NULL)
		return (NONE);
	if (ft_strlen(input) == 0)
		return (NONE);
	if (ft_strncmp(input, "exit", 5) == 0) // TODO use a builtin
	{
		rl_clear_history();
		return (EXIT);
	}
	add_history(input);
	return (SUCCESS);
}

static int	main_minishell(t_minishell *minishell, t_list *tokens)
{
	t_cmd	*cmd;

	cmd = parser(tokens, minishell);
	if (set_command(tokens, cmd) == ERROR)
		return (ERROR);
	if (execute(cmd, minishell) != 0)
	{
		perror("Command not found");
		return (ERROR);
	}
	return (SUCCESS);
}

static int	main_loop(t_minishell *minishell)
{
	int		cmd_code;
	t_list	*tokens;

	while (!minishell->should_exit)
	{
		minishell->cmd_input = readline(minishell->prompt_msg);
		cmd_code = check_input_term(minishell->cmd_input);
		if (cmd_code == EXIT)
		{
			free(minishell->cmd_input);
			free(minishell->prompt_msg);
			return (SUCCESS);
		}
		if (cmd_code == NONE)
			continue ;
		tokens = tokenizer(minishell->cmd_input);
		if (tokens == NULL)
			return (ERROR);
		//if (check_valid_tokens(tokens) == SUCCESS) // FIXME -> par en infinite loop quand y'a un |
		main_minishell(minishell, tokens);
		//else
			//printf("prout");
			//free_tokens(tokens); ////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< TODO
		free(minishell->cmd_input);
	}
	return (SUCCESS);
}

#include <termios.h>

int	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	struct termios old_termios, new_termios;
	tcgetattr(0,&old_termios);

	signal(SIGINT, handler);

	new_termios             = old_termios;
	new_termios.c_cc[VEOF]  = 3; // ^C
	new_termios.c_cc[VINTR] = 4; // ^D
								 // TODO add the ctrl C print
	tcsetattr(0,TCSANOW,&new_termios);

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



	tcsetattr(0,TCSANOW,&old_termios);

	return (0);
}
