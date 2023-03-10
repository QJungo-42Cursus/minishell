#ifndef TEST
#define TEST
#endif

#include "all.hpp"
#include "unistd.h"
#include "gtest/gtest.h"

extern "C" {
int w_exit_status(int es) { return WEXITSTATUS(es); }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

void minishell(const char *cmd_input, int &exit_code) {
  t_minishell *g_minishell = new t_minishell();
  if (init_minishell(g_minishell, environ) != SUCCESS)
    FAIL() << "init_minishell failed";
  g_minishell->cmd_input = (char *)cmd_input;
  int cmd_code = check_input_term(g_minishell->cmd_input);
  if (cmd_code == EXIT)
    return;
  t_list *tokens = tokenizer(g_minishell->cmd_input, FALSE);
  if (tokens == NULL || check_valid_tokens(tokens) != SUCCESS)
    return;
  exit_code = main_minishell(g_minishell, tokens);
}

void bash(const char *cmd_input, int &exit_code) {
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
  dprintf(pipefd[STDOUT_FILENO], "%s\n", cmd_input);
  close(pipefd[STDOUT_FILENO]);
  waitpid(pid, &exit_code, 0);
  exit_code = w_exit_status(exit_code);
}

#define COMPARE(cmd_input)                                                     \
  {                                                                            \
    int bash_exit_code = 0;                                                    \
    int minishell_exit_code = 0;                                               \
    std::string minishell_output;                                              \
    std::string bash_output;                                                   \
                                                                               \
    ::testing::internal::CaptureStdout();                                      \
    minishell(cmd_input, minishell_exit_code);                                 \
    minishell_output = ::testing::internal::GetCapturedStdout();               \
                                                                               \
    ::testing::internal::CaptureStdout();                                      \
    bash(cmd_input, bash_exit_code);                                           \
    bash_output = ::testing::internal::GetCapturedStdout();                    \
                                                                               \
    ASSERT_EQ(bash_exit_code, minishell_exit_code);                            \
    ASSERT_EQ(bash_output, minishell_output);                                  \
    /* std::cout << "exit_code : " << bash_exit_code << "msh "                 \
              << minishell_exit_code << std::endl; */                          \
    /* std::cout << minishell_output << std::endl;*/                           \
  }

TEST(End2End, echo) {
  COMPARE("echo hello");
  COMPARE("echo -n hello");
}

TEST(End2End, echoPipe) { COMPARE("echo hello | cat -e"); }

TEST(End2End_Eval, forkExecve) {
  COMPARE("/bin/ls");
  COMPARE("/bin/ls -laF");
  COMPARE("/bin/ls -l -a -F");
}

TEST(End2End_Eval, builtins_echo) { COMPARE("echo \"it works\""); }

TEST(End2End_Eval, builtins_exit) { COMPARE("exit"); }

// ne met pas dans le meme ordre...
// TEST(End2End_Eval, builtins_env) { COMPARE("env"); }
