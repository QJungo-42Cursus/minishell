#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "tokenizer/tokenizer.h"
#include "libft/libft.h"

#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/wait.h"

#define PADDING "----------------------------------------"

void title(char *str, char *line)
{
	ft_color(BLUE, BOLD);
	printf("%s %s\n", PADDING, str);
	ft_color(RESET, RESET);
	printf("%s\n", line);
}
void foot(t_list *tokens)
{
	ft_printf("result : ");
	log_tokens(tokens);
	ft_color(PURPLE, BOLD);
	printf("\n%s END\n\n", PADDING);
	ft_color(RESET, RESET);
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
	free(line);
}

/* TEST TOKENIZER */
void test()
{
	in(TRUE, ft_strdup("echo \" salut\\\" \"               \"     ")); // ERROR DQUOTE not closed
	in(FALSE, ft_strdup("echo \" salut\\\" \" ")); // OK
	in(FALSE, ft_strdup("echo \" salut\\\" \" \"\"     ")); // DQUOTE empty and nothiing after
	in(FALSE, ft_strdup("echo salut\" s\"")); // DQUOTE after word, should concat auto
	in(FALSE, ft_strdup("echo ' salut ' ")); // OK
	in(FALSE, ft_strdup("echo ' salut\\'  '' ")); // QUOTE empty and nothiing after
	in(FALSE, ft_strdup("echo salut' s'  ")); // QUOTE after word, should concat auto
	//in(TRUE, ft_strdup("echo ' salut\\'                '     ")); // ERROR QUOTE not closed
}

int main()
{
	//line = readline("prompt> ");
	test();
}
