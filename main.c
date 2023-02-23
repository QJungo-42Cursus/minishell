/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:00:26 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/23 20:47:24 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <termios.h>
// nous
#include "libft/libft.h"
#include "tokenizer/tokenizer.h"
#include "env/env.h"
#include "builtins/builtins.h"
#include "tests/debug_helper.hpp"
#include "minishell.h"
#include "executor/executor.h"
#include "token_checker/token_checker.h"

typedef struct s_transmitter_signal {
	int	exit;
	int	exit_under_process;
}	t_transmit_signal;

void	parent_handler(int sig)
{
	/*
	if (sig == 2)
		exit(0);
		*/
	(void) sig;
	printf("Coucou\n");
}

enum e_cmd_code {
	NONE = 1,
	EXIT = 2,
};

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
	int		i;
	void	**tokens_to_free;

	tokens_to_free = token_free_list(tokens);
	cmd = parser(tokens, minishell);
	if (cmd == NULL)
		return (ERROR);
	exit_status = execute(cmd, minishell);
	free_ast(cmd);
	i = 0;
	while (tokens_to_free[i] != NULL)
	{
		free(tokens_to_free[i]);
		//free(((t_list *)tokens_to_free[i])->content); // TODO
		i++;
	}
	free(tokens_to_free);
	return (exit_status);
}

int	main_loop(t_minishell *minishell)
{
	t_list	*tokens;
	char	*cmd_input;

	while (!minishell->should_exit)
	{
		cmd_input = readline(minishell->prompt_msg);
		if (cmd_input == NULL || ft_strlen(cmd_input) == 0)
			continue ;
		add_history(cmd_input);
		tokens = tokenizer(cmd_input, FALSE);
		if (tokens == NULL)
			return (ERROR);
		if (check_valid_tokens(tokens) == SUCCESS)
			main_minishell(minishell, tokens);
		free(cmd_input);
	}
	return (SUCCESS);
}

static void	set_termios(void)
{
	struct sigaction	new_sigaction;
	struct sigaction	old_sigaction;
	struct termios		old_termios;
	struct termios		new_termios;

	tcgetattr(0, &old_termios);
	new_termios = old_termios;
	new_termios.c_cc[VEOF] = 3;
	new_termios.c_cc[VINTR] = 4;
	tcsetattr(0, TCSANOW, &new_termios);
	new_sigaction.sa_handler = parent_handler;
	sigaction(SIGINT, &new_sigaction, &old_sigaction);
}
// new_termios.c_cc[VEOF] = 3; // ^C
// new_termios.c_cc[VINTR] = 4; // ^D

#ifndef TEST
int	main(int argc, char **argv, char **envp)
{
	t_minishell		minishell;

	set_termios();
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
	// tcsetattr(0, TCSANOW, &old_termios); // TODO -> dans le exit !
	return (0);
}
#endif
