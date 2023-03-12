/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 13:35:14 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/11 19:47:02 by qjungo           ###   ########.fr       */
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

/// ownership return in run_minishell()
static void	**get_token_to_free_list(t_list *tokens)
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

static void	free_token_list(void **tokens_to_free, t_bool free_content)
{
	int		i;

	i = 0;
	while (tokens_to_free[i] != NULL)
	{
		if (free_content && ((t_list *)tokens_to_free[i])->content != NULL)
			free(((t_list *)tokens_to_free[i])->content);
		free(tokens_to_free[i]);
		i++;
	}
	free(tokens_to_free);
}

extern volatile sig_atomic_t	g_minishell_status;

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
		free_token_list(tokens_to_free, TRUE);
		return (ERROR);
	}
	minishell->current_ast = cmd;
	if (g_minishell_status != S_HEREDOC_ABORT)
	{
		execute(cmd, minishell);
		g_minishell_status = S_PROMPT;
	}
	free_ast(cmd);
	free_token_list(tokens_to_free, FALSE);
	return (SUCCESS);
}

static void	restore_stdin(int stdin_fd)
{
	if (g_minishell_status == S_HEREDOC_ABORT)
	{
		g_minishell_status = S_PROMPT;
		dup2(stdin_fd, STDIN_FILENO);
		ft_putstr_fd("\n", 1);
	}
}

// free OK !
/// give ownership of tokens at each while iteration (it to free)
int	main_loop(t_minishell *minishell)
{
	t_list				*tokens;
	char				*cmd_input;
	int					stdin_fd;

	while (!minishell->should_exit)
	{
		restore_stdin(stdin_fd);
		cmd_input = readline(minishell->prompt_msg);
		stdin_fd = dup(STDIN_FILENO);
		if (cmd_input == NULL)
			exit_(minishell, NULL, 0);
		if (ft_strlen(cmd_input) == 0)
			continue ;
		tokenizer(cmd_input, &tokens, FALSE, minishell);
		if (tokens == NULL)
			continue ;
		add_history(cmd_input);
		free(cmd_input);
		if (check_valid_tokens(tokens) == SUCCESS)
			run_minishell(minishell, tokens);
		else
			free_token_list(get_token_to_free_list(tokens), TRUE);
	}
	return (SUCCESS);
}
