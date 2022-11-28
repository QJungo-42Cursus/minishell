#include "libft/libft.h"		// ...
#include <stdio.h>				// ...
#include <stdlib.h>				// ...
#include <unistd.h>				// ...

#include <readline/readline.h>	// readline lib
#include <readline/history.h>	// readline history

#include "tokenizer/tokenizer.h"
#include "libft/libft.h"

#include "fcntl.h"
#include "sys/wait.h"

#define PADDING "----------------------------------------"
int	old_main()
{
	char *line;
	char *prompt_msg;

	char current_dir[2048];
	getcwd(current_dir, 2048);
	printf("dir : %s \n", current_dir);
	prompt_msg = ft_sprintf("%s %s %s", "hostname", current_dir, " > ");

	while (1)
	{
		line = readline(prompt_msg);
		if (line == NULL)
		{
			// Ca arrive quand on lache un Ctrl-D
			rl_clear_history();
			printf("EOF rl_clear_history\n");
			continue;
		}
		if (ft_strlen(line) == 0)
		{
			// Ca arrive quand on enter sans rien...
			//printf("ligne vide\n");
			rl_replace_line("ligne videe...", 10);
			rl_redisplay();
			continue;
		}
		add_history(line);
		int c = rl_on_new_line();
		printf("rl_on_new_line : %d\n", c);
		free(line);
	}
	printf("line: %s", line);
}

void title(char *str, char *line)
{
	ft_color(BLUE, BOLD);
	printf("%s %s\n", PADDING, str);
	fflush ( stdout );
	printf("%s\n", line);
	ft_color(RESET, RESET);
	fflush ( stdout );
}

void foot(t_list *tokens)
{
	ft_printf("result : ");
	fflush ( stdout );
	ft_color(PURPLE, BOLD);
	fflush ( stdout );
	log_tokens(tokens);
	printf("\n%s END\n\n", PADDING);
	fflush ( stdout );
	ft_color(RESET, RESET);
	fflush ( stdout );
}

void in(t_bool error, char *line)
{
	if (error)
	{
		char *tmp = ft_strdup(line);
		if (fork() == 0) // Fork pour pouvoir crash !
		{
			// TODO pour l'instant, ca me fait un malloc error
			title("Error mode", tmp);
			foot(tokenizer(tmp));
			free(line);
			return ;
		}
		else
		{
			wait(NULL);
			return ;
		}
	}
	title("Normal mode", line);
	foot(tokenizer(line));
	//free(line);
}

/* TEST TOKENIZER */
void test()
{
	//in(FALSE, ft_strdup("echo salut && echo bye\""));
	in(FALSE, ft_strdup("echo \"\"salut"));
	in(FALSE, ft_strdup("echo salut <<&&>> echo bye"));
	in(FALSE, ft_strdup("echo"));
	in(FALSE, ft_strdup("echo"));
	in(FALSE, ft_strdup("echo"));
	in(FALSE, ft_strdup("echo"));
	in(FALSE, ft_strdup("echo"));
	// la premiere ligne fonctionne, mais la deuxieme plante segfault... comme si l'une empechait l'autre d'exister
	in(FALSE, ft_strdup("echo salut < > &> &2> 22 <<&&>> echo bye"));
	in(FALSE, ft_strdup("echo salut < > &> &2> 22 <<&&>> echo bye"));
	in(FALSE, ft_strdup("echo salut < > &> &2> 22 <<&&>> echo bye"));
	return ;
	in(FALSE, ft_strdup("echo \"salut < > &> &2> 22 <<&&>> echo bye"));
	in(FALSE, ft_strdup("echo salut > salut 2> >"));
	in(FALSE, ft_strdup("echo salut>salut"));
	in(FALSE, ft_strdup("echo salut >"));
	in(FALSE, ft_strdup("echo salut >> || << && ;"));

	//in(TRUE, ft_strdup("echo \" salut\\\" \"               \"     ")); // ERROR DQUOTE not closed
	in(FALSE, ft_strdup("echo \" salut\\\" \" ")); // OK
	in(FALSE, ft_strdup("echo salut\" s\"")); // DQUOTE after word, should concat auto
	in(FALSE, ft_strdup("echo ' salut ' ")); // OK
	in(FALSE, ft_strdup("echo ' salut\\'  '' ")); // QUOTE empty and nothiing after
	in(FALSE, ft_strdup("echo salut' s'  ")); // QUOTE after word, should concat auto
	//in(TRUE, ft_strdup("echo ' salut\\'                '     ")); // ERROR QUOTE not closed
}

int main()
{
	//char *line = readline("prompt> "); (void)line;
	test();
}
