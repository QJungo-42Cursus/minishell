#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <sys/wait.h>
// nous
#include "libft/libft.h"
#include "tokenizer/tokenizer.h"
#include "env/env.h"
#include "builtins/builtins.h"
#include "tests/debug_helper.h"
#include "minishell.h"
#include "executor/executor.h"
#include "token_checker/token_checker.h"

void	handler(int num)
{
	// TODO avec CAT, ne doit pas quitter le shell (?)
	if (num == 2)
		exit(0);
}

enum e_cmd_code {
	NONE = 1,
	EXIT = 2,
};

int	check_input_term(char *input, t_minishell *minishell)
{
	if (input == NULL)
		return (NONE);
	if (ft_strlen(input) == 0)
		return (NONE);
	if (ft_strncmp(input, "exit", 5) == 0) // TODO use a builtin
	{
		rl_clear_history();
		exit_(minishell, NULL, 0);
		return (EXIT);
	}
	add_history(input);
	return (SUCCESS);
}

void	**token_free_list(t_list *tokens)
{
	t_list	*tmp;
	void	**result;
	int		i;

	result = (void **)malloc(sizeof(void *) * (ft_lstsize(tokens) + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	tmp = tokens;
	while (tmp != NULL)
	{
		result[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	main_minishell(t_minishell *minishell, t_list *tokens)
{
	t_cmd	*cmd;
	int		exit_status;
	void	**tokens_to_free;

	tokens_to_free = token_free_list(tokens);
	cmd = parser(tokens, minishell);
	if (cmd == NULL)
		return (ERROR);
	exit_status = execute(cmd, minishell);
	free_ast(cmd);

	int i = 0;
	while (tokens_to_free[i] != NULL)
	{
		free(tokens_to_free[i]);
		//free(((t_list *)tokens_to_free[i])->content); // nope
		i++;
	}
	free(tokens_to_free);


	return (exit_status);
}

/*static*/ int	main_loop(t_minishell *minishell)
{
	int		cmd_code;
	t_list	*tokens;
	char	*cmd_input;

	while (!minishell->should_exit)
	{
		cmd_input = readline(minishell->prompt_msg);
		cmd_code = check_input_term(cmd_input, minishell);
		if (cmd_code == EXIT)
		{
			free(cmd_input);
			free(minishell->prompt_msg);
			return (SUCCESS);
		}
		if (cmd_code == NONE)
			continue ;
		tokens = tokenizer(cmd_input, FALSE);
		if (tokens == NULL)
			return (ERROR);
		if (check_valid_tokens(tokens) == SUCCESS)
			main_minishell(minishell, tokens);
		free(cmd_input);
	}
	return (SUCCESS);
}

#include <termios.h>
#ifndef TEST
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
#endif
