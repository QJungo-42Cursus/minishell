#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <termios.h>
#include <sys/wait.h>
// nous
#include "libft/libft.h"
#include "tokenizer/tokenizer.h"
#include "minishell.h"
#include "executor/executor.h"
#include "token_checker/token_checker.h"
#include "builtins/builtins.h"

int g_pid;

void	signal_handler(int sig)
{
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	signal_handler_child(int sig)
{

	kill(SIGKILL, g_pid);
}

void super_fork(void)
{
	char *arg_list[] = {"sleep", "10", NULL};
	printf("start\n");
	execvp("/bin/sleep", arg_list);
}
int main(int argc, char **argv, char **envp)
{
	char	*cmd_input;

	struct sigaction	prompt_sa;
	struct sigaction	exec_sa;

	prompt_sa.sa_handler = signal_handler;
	exec_sa.sa_handler = signal_handler_child;
	sigaction(SIGINT, &prompt_sa, NULL);
	while (TRUE)
	{
		cmd_input = readline("minishell$ ");
		printf("cmd_input: %s\n", cmd_input);
		if (cmd_input == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (ft_strlen(cmd_input) == 0)
			continue ;
		add_history(cmd_input);
		free(cmd_input);
		sigaction(SIGINT, &exec_sa, NULL);
		g_pid = fork();
		if (g_pid == 0)
			super_fork();
		wait(0);
		printf("end\n");
		sigaction(SIGINT, &prompt_sa, NULL);
	}
}
