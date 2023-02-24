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
#include <termios.h>
// nous
#include "libft/libft.h"
#include "tokenizer/tokenizer.h"
#include "minishell.h"
#include "executor/executor.h"
#include "token_checker/token_checker.h"
#include "builtins/builtins.h"

/************************************ TERMIOS && SIGNALS ************************************/
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

void	set_termios(void)
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

	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		// TODO: ca va ici ? return (ERROR) ?
		errno = EINVAL;
		perror("./minishell error with stream");
		exit (-1);
	}
}
// new_termios.c_cc[VEOF] = 3; // ^C
// new_termios.c_cc[VINTR] = 4; // ^D

static void unset_termios(void)
{
	// TODO
}

/************************************ MINISHELL ************************************/

/// ownership return in run_minishell()
// free TODO
// malloc OK !
void	**get_token_to_free_list(t_list *tokens)
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

void free_token_list(void **tokens_to_free)
{
	int		i;

	i = 0;
	while (tokens_to_free[i] != NULL)
	{
		free(tokens_to_free[i]);
		//free(((t_list *)tokens_to_free[i])->content);
		i++;
	}
	free(tokens_to_free);
}

// free TODO
static int	run_minishell(t_minishell *minishell, t_list *tokens)
{
	t_cmd	*cmd;
	void	**tokens_to_free;

	tokens_to_free = get_token_to_free_list(tokens);
	if (tokens_to_free == NULL)
		return (ERROR);
	cmd = parser(tokens, minishell);
	if (cmd == NULL)
	{
		free_token_list(tokens_to_free);
		return (ERROR);
	}
	minishell->current_ast = cmd;
	execute(cmd, minishell);
	free_ast(cmd);
	free_token_list(tokens_to_free);
	return (SUCCESS);
}

// free OK !
/// give ownership of tokens at each while iteration (it to free)
static int	main_loop(t_minishell *minishell)
{
	t_list	*tokens;
	char	*cmd_input;

	while (!minishell->should_exit)
	{
		tokens = NULL;
		cmd_input = readline(minishell->prompt_msg);
		if (cmd_input == NULL || ft_strlen(cmd_input) == 0)
			continue ;
		add_history(cmd_input);
		if (tokenizer(cmd_input, &tokens, FALSE) == ERROR)
		{
			free(cmd_input);
			exit_(minishell, NULL, 1);
			return (ERROR);
		}
		free(cmd_input);
		if (tokens == NULL)
			continue ;
		if (check_valid_tokens(tokens) == SUCCESS)
			if (run_minishell(minishell, tokens) == ERROR)
				return (ERROR);
	}
	return (SUCCESS);
}

#ifndef TEST
/// no keep the ownership of minishell
// free OK !
int	main(int argc, char **argv, char **envp)
{
	t_minishell		minishell;

	(void) argv;
	//set_termios();
	if (argc != 1)
	{
		write(2, "Usage: ./minishell {don't use any arguments}\n", 45);
		unset_termios();
		exit (1);
	}
	if (init_minishell(&minishell, envp) == ERROR)
	{
		unset_termios();
		exit (1);
	}
	return (main_loop(&minishell));
	// tcsetattr(0, TCSANOW, &old_termios); // TODO -> dans le exit !
}
#endif
