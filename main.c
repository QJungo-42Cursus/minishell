/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:00:26 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 22:28:38 by qjungo           ###   ########.fr       */
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
#include "minishell.h"

/********************** TERMIOS && SIGNALS ************************************/

t_minishell_status	g_minishell_status = S_PROMPT;

void	signal_handler(int sig)
{
	(void) sig;

	if (g_minishell_status == S_PROMPT || g_minishell_status == S_EXEC)
		ft_putstr_fd("\n", 1);
	if (g_minishell_status == S_PROMPT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (g_minishell_status == S_HEREDOC)
	{
		g_minishell_status = S_HEREDOC_ABORT;
	}
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

void	free_token_list(void **tokens_to_free)
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
	if (g_minishell_status != S_HEREDOC_ABORT)
	{
		execute(cmd, minishell);
		g_minishell_status = S_PROMPT;
	}
	free_ast(cmd);
	free_token_list(tokens_to_free);
	return (SUCCESS);
}

// free OK !
/// give ownership of tokens at each while iteration (it to free)
static int	main_loop(t_minishell *minishell, struct sigaction *prompt_sa)
{
	t_list				*tokens;
	char				*cmd_input;

	(void) prompt_sa;
	while (!minishell->should_exit)
	{
		sigaction(SIGINT, prompt_sa, minishell->m_exec_sa);
		cmd_input = readline(minishell->prompt_msg);
		if (cmd_input == NULL)
		{
			printf("exit\n");
			exit_(minishell, NULL, 0);
			exit(0);
		}
		if (ft_strlen(cmd_input) == 0)
			continue ;
		add_history(cmd_input);
		tokenizer(cmd_input, &tokens, FALSE, minishell);
		free(cmd_input);
		if (tokens == NULL)
			continue ;
		if (check_valid_tokens(tokens) == SUCCESS)
			run_minishell(minishell, tokens);
	}
	return (SUCCESS);
}

#ifndef TEST
/// no keep the ownership of minishell
// free OK !
int	main(int argc, char **argv, char **envp)
{
	t_minishell			minishell;
	struct sigaction	exec_sa;
	struct sigaction	prompt_sa;

	(void) argv;
	sigaction(SIGINT, NULL, &prompt_sa);
	prompt_sa.sa_handler = signal_handler;
	minishell.m_exec_sa = &exec_sa;
	sigaction(SIGINT, &prompt_sa, minishell.m_exec_sa);
	if (argc != 1)
	{
		write(2, "Usage: ./minishell {don't use any arguments}\n", 45);
		exit(1);
	}
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_putstr_fd("./minishell error with stream\n", 2);
		exit(1);
	}
	if (init_minishell(&minishell, envp) == ERROR)
	{
		exit(1);
	}
	return (main_loop(&minishell, &prompt_sa));
}
#endif
