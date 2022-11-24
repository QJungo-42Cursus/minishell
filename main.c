#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "tokenizer/tokenizer.h"
#include "libft/libft.h"

int main() {

	char *line;
	//line = readline("prompt> ");

	/* TEST TOKENIZER */
	//line = ft_strdup("echo \" salut\\\" \" "); // OK
	//line = ft_strdup("echo hello world \" \\\"  salut (avec une chiee d'espace !!!)\"et_un_truc_colle_a_la_fin fin voila quoi... \"\"dquotes_vides");
	//line = ft_strdup("echo \" salut\\\" \"               \"     "); // ERROR DQUOTE not closed
	//line = ft_strdup("echo \" salut\\\" \" \"\"     "); // DQUOTE empty and nothiing after
	line = ft_strdup("echo salut\" s\""); // DQUOTE after word, should concat auto


	printf("line: %s\n len: %d\n\n", line, ft_strlen(line));
	t_list *tokens = tokenizer(line);
	printf("\n");
	(void) tokens;
}
