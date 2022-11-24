#include <stdio.h>
#include <readline/readline.h>
//#include <readline/history.h>

#include "tokenizer/tokenizer.h"
#include "libft/libft.h"

// test la fonction readline
int main() {

	char *line = readline("prompt> ");
	
	printf("line: %s", line);

	t_list *tokens = tokenizer(line);
	(void) tokens;
}
