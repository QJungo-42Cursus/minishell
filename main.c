#include <stdio.h>
#include <readline/readline.h>
//#include <readline/history.h>

// test la fonction readline
int main() {

	char *line = readline("prompt> ");
	
	//char *line = "salut";
	printf("line: %s", line);
}
