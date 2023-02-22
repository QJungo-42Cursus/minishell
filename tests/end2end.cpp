#ifndef TEST
#define TEST
#endif

#include "unistd.h"
#include "gtest/gtest.h"

extern "C" {
#include "../builtins/cd.c"
#include "../builtins/echo.c"
#include "../builtins/env.c"
#include "../builtins/exit_.c"
#include "../builtins/export.c"
#include "../builtins/pwd.c"
#include "../builtins/unset.c"
#include "../env/cpy_envp.c"
#include "../env/find_command_path.c"
#include "../env/get_env_var_index.c"
#include "../env/get_env_var_value.c"
#include "../env/get_paths_in_env.c"
#include "../executor/execute_pipeline.c"
#include "../executor/executor.c"
#include "../executor/executor_utils.c"
#include "../minishell_utils.c"
#include "../parser/parse_command.c"
#include "../parser/parse_pipeline.c"
#include "../parser/parser_utils.c"
#include "../tokenizer/set_next_token_position.c"
#include "../tokenizer/tokenizer.c"

#include "../parser/parser.c"

#include "../expansion/expansion.c"
#include "../expansion/expend_dollar.c"
#include "../expansion/get_var_position.c"
#include "../expansion/unquote.c"
// #include "../token_checker/token_checker_main.c"
// #include "../token_checker/token_checker_utils.c"

#include "../main.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

int main(int argc, char **argv, char **envp) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(End2End, Test) {
  int pipefd[2];
  int pid;

  ASSERT_TRUE(pipe(pipefd) == 0);

  pid = fork();
  ASSERT_TRUE(pid >= 0);
  if (pid == 0) {
    dup2(pipefd[STDIN_FILENO], STDIN_FILENO);
    close(pipefd[STDOUT_FILENO]);
    close(pipefd[STDIN_FILENO]);
    execv("/bin/bash", NULL);
  }
  close(pipefd[STDIN_FILENO]);
  dprintf(pipefd[STDOUT_FILENO], "echo hello\n");
  close(pipefd[STDOUT_FILENO]);
  waitpid(pid, NULL, 0);
}

int main_loop_(char *cmd_input) {
  t_minishell *minishell;
  minishell->cmd_input = cmd_input;
  //int cmd_code = check_input_term(minishell->cmd_input);
  int cmd_code = 0;
  if (cmd_code == EXIT) {
    free(minishell->cmd_input);
    free(minishell->prompt_msg);
    return (SUCCESS);
  }
  t_list *tokens = tokenizer(minishell->cmd_input, FALSE);
  if (tokens == NULL)
    return (ERROR);

  return check_valid_tokens(tokens) == SUCCESS
             ? main_minishell(minishell, tokens)
             : ERROR;
}
