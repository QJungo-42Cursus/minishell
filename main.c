/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:00:26 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 19:47:00 by agonelle         ###   ########.fr       */
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

/********************** TERMIOS && SIGNALS ************************************/

int		g_is_executing = FALSE;

void	signal_handler(int sig)
{
	(void) sig;
	ft_putstr_fd("\n", 1);
	if (g_is_executing)
		return ;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/******************************* MINISHELL ************************************/

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
		i++;
	}
	free(tokens_to_free);
}

// free TODO
/// If an error occurs, the function will quit by itself
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
	t_list				*tokens;
	char				*cmd_input;
	struct sigaction	prompt_sa;
	struct sigaction	exec_sa;

	minishell->m_exec_sa = &exec_sa;
	prompt_sa.sa_handler = signal_handler;
	sigaction(SIGINT, &prompt_sa, minishell->m_exec_sa);
	while (!minishell->should_exit)
	{
		tokens = NULL;
		cmd_input = readline(minishell->prompt_msg);
		if (cmd_input == NULL)
		{
			printf("exit\n");
			free(cmd_input);
			exit_(minishell, NULL, 0);
		}
		if (ft_strlen(cmd_input) == 0)
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
		{
			// TODO a chque exec, (dans t_minishell) 
			run_minishell(minishell, tokens);
		}
		g_is_executing = 0;
		sigaction(SIGINT, &prompt_sa, minishell->m_exec_sa);
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
		exit (1);
	}
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		// TODO: ca va ici ? return (ERROR) ?
		errno = EINVAL;
		perror("./minishell error with stream");
		exit (1);
	}
	if (init_minishell(&minishell, envp) == ERROR)
	{
		exit (1);
	}
	return (main_loop(&minishell));
	// tcsetattr(0, TCSANOW, &old_termios); // TODO -> dans le exit !
}
#endif
