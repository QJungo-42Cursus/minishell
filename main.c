#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "tokenizer/tokenizer.h"
#include "libft/libft.h"

#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/wait.h"


void in(t_bool error, char *line)
{
	t_list		*tokens;

	if (error)
	{
		printf("Error mode -------------\n");
		if (fork() == 0) // Fork pour pouvoir crash !
		{
			printf("line: %s\n len: %d\n\n", line, ft_strlen(line));
			tokens = tokenizer(line);
			free(line);
			printf("\n");
			return ;
		}
		else
		{
			wait(NULL);
			return ;
		}
		printf("-------------------- fin error\n\n");
	}
	printf("Mode success -------------\n");

	printf("line: %s\n len: %d\n\n", line, ft_strlen(line));
	tokens = tokenizer(line); (void)tokens;
	printf("\n");

	free(line);
	printf("-------------------- fin success\n\n");
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
