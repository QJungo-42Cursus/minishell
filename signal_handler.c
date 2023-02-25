/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:33:22 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/25 15:08:12 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include "libft/libft.h"
#include "minishell.h"

extern volatile sig_atomic_t	g_minishell_status;

static void	handle_sigint(void)
{
	if (g_minishell_status == S_PROMPT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (g_minishell_status == S_HEREDOC)
	{
		close(STDIN_FILENO);
		g_minishell_status = S_HEREDOC_ABORT;
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
