#include <stdio.h>
#include <readline/readline.h>
//#include <readline/history.h>

#include "tokenizer/tokenizer.h"
#include "libft/libft.h"

// test la fonction readline
int main() {

	char *line;
	//line = readline("prompt> ");
	line = "echo hello world \" \\\"  salut (avec une chiee d'espace !!!)\"et_un_truc_colle_a_la_fin fin voila quoi... \"\"dquotes_vides";

	printf("line: %s\n", line);
	t_list *tokens = tokenizer(line);
	printf("\n");
	(void) tokens;
}
