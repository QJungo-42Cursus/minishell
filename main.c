/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:00:26 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/11 10:53:08 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "minishell.h"

volatile sig_atomic_t	g_minishell_status = S_PROMPT;

#ifndef TEST
/// no keep the ownership of minishell
// free OK !
int	main(int argc, char **argv, char **envp)
{
	t_minishell			minishell;

	(void) argv;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	if (argc != 1)
	{
		ft_putstr_fd("Usage: ./minishell {don't use any arguments}\n", 2);
		exit(1);
	}
	if (!isatty(0) || !isatty(1) || !isatty(2))
	{
		ft_putstr_fd("./minishell error with stream\n", 2);
		exit(1);
	}
	if (init_minishell(&minishell, envp) == ERROR)
		exit(1);
	return (main_loop(&minishell));
}
#endif
