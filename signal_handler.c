/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:33:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/25 14:07:51 by qjungo           ###   ########.fr       */
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

extern volatile sig_atomic_t	g_minishell_status;

static void	handle_sigint(void)
{
	int		to_reopen;

	if (g_minishell_status == S_PROMPT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_minishell_status == S_HEREDOC)
	{
		to_reopen = dup(STDIN_FILENO);
		g_minishell_status = S_HEREDOC_ABORT;
		close(STDIN_FILENO);
		//rl_replace_line("", 0);
		//rl_on_new_line();
		//rl_redisplay();
		dup2(to_reopen, STDIN_FILENO);
		ft_putstr_fd("\n", 1);
	}
}

static void	handle_sigquit(void)
{
	if (g_minishell_status == S_PROMPT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
		handle_sigint();
	if (sig == SIGQUIT)
		handle_sigquit();
}
