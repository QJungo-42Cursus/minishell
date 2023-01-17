#include "libft/libft.h"       // ...
#include <stdio.h>             // ...
#include <stdlib.h>            // ...
#include <unistd.h>            // ...
#include <readline/history.h>  // readline history
#include <readline/readline.h> // readline lib

#include "fcntl.h"
#include "libft/libft.h"
#include "sys/wait.h"
#include "tokenizer/tokenizer.h"

#include "tests/debug_helper.h"

int main(int argc, char **argv, char **envp) {
  (void)argc;
  (void)argv;
  (void)envp;
  char *cmd_input;
  char *prompt_msg;

  char current_dir[2048];
  getcwd(current_dir, 2048);
  printf("dir : %s \n", current_dir);
  prompt_msg = ft_sprintf("%s %s %s", "hostname", current_dir, " > ");

  while (1) {
    cmd_input = readline(prompt_msg);


    if (cmd_input == NULL) {
      // Ca arrive quand on lache un Ctrl-D
      rl_clear_history();
      printf("EOF rl_clear_history\n");
      continue;
    }
    if (ft_strlen(cmd_input) == 0) {
      // Ca arrive quand on enter sans rien...
      // printf("ligne vide\n");
      rl_replace_line("ligne videe...", 10);
      rl_redisplay();
      continue;
    }
    if (ft_strncmp(cmd_input, "exit", 4) == 0) {
      rl_clear_history();
      printf("exit rl_clear_history\n");
      break;
    }

	t_list *tokens = tokenizer(cmd_input); (void)tokens; LOG_TOKENS(tokens);

    add_history(cmd_input);
    int c = rl_on_new_line();
    printf("rl_on_new_line : %d\n", c);

    free(cmd_input);
  }
  printf("cmd_input: %s", cmd_input);
}
