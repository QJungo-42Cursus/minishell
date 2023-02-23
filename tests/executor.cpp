#include "parserAndExecutor.hpp"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <vector>

extern "C" {
int w_exit_status(int es) { return WEXITSTATUS(es); }
int execute(t_cmd *cmd, t_minishell *minishell);
#include "../env/env.h"
}
extern char **g_envp;

void test_exec(t_cmd *cmd, std::string stdout_expected,
               std::string stderr_expected, int exit_status_expected) {
  t_minishell *minishell = NULL;
  minishell = (t_minishell *)malloc(sizeof(t_minishell));
  minishell->env_copy = cpy_envp(g_envp);
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();

  int exit_status = execute(cmd, minishell);

  std::string stdout_res = testing::internal::GetCapturedStdout();
  std::string stderr_res = testing::internal::GetCapturedStderr();
  EXPECT_EQ(stdout_res, stdout_expected);
  EXPECT_EQ(stderr_res, stderr_expected);
  EXPECT_EQ(exit_status, exit_status_expected);
}

void test_redir_out(std::string filename, std::string expected) {
  std::ifstream file(filename);
  std::string content((std::istreambuf_iterator<char>(file)),
                      (std::istreambuf_iterator<char>()));
  ASSERT_EQ(content, expected);
}

TEST(Executor, SimpleCommand) {
  t_cmd *cmd = new_cmd(COMMAND);
  cmd->s_command.argv = setup_argv({"/bin/echo", "hi friends !"});
  test_exec(cmd, "hi friends !\n", "", 0);
}

/* TODO les 2 qui fails avec github action mais pas en local */
TEST(Executor, aSimpleFailingPipeline) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->s_pipeline.pipe_count = 2;
  cmd->s_pipeline.pids = new int[2];
  cmd->s_pipeline.pipes = new int[4];
  cmd->s_pipeline.first_cmd = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->s_pipeline.first_cmd->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.argv =
      setup_argv({"/bin/bc", "not_here_file"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next = NULL;
  test_exec(cmd, "", "File not_here_file is unavailable.\n", 1);
}

/*
TEST(Executor, aThreeCommandsPipelineAndFail) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->s_pipeline.pipe_count = 3;
  cmd->s_pipeline.pids = new int[3];
  cmd->s_pipeline.pipes = new int[6];
  cmd->s_pipeline.first_cmd = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.argv =
      setup_argv({"/bin/ls", "tests/test_files"});
  cmd->s_pipeline.first_cmd->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.argv = setup_argv({"/bin/cat", "-e"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next->s_command.argv =
      setup_argv({"/bin/bc", "not_here_file"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next->s_command.next = NULL;
  test_exec(cmd, "", "File not_here_file is unavailable.\n", 1);
}
*/

TEST(Executor, SimpleFailingCommand) {
  t_cmd *cmd = new_cmd(COMMAND);
  cmd->s_command.argv = setup_argv({"/bin/bc", "not_here_file"});
  test_exec(cmd, "", "File not_here_file is unavailable.\n", 1);
}

TEST(Executor, SimplePipeline) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->s_pipeline.pipe_count = 2;
  cmd->s_pipeline.pids = new int[2];
  cmd->s_pipeline.pipes = new int[4];
  cmd->s_pipeline.first_cmd = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->s_pipeline.first_cmd->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.argv = setup_argv({"/bin/cat", "-e"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next = NULL;
  test_exec(cmd, "hi friends !$\n", "", 0);
}

/*  `cat | ls`
TEST(Executor, TrickyPipeline) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->s_pipeline.pipe_count = 2;
  cmd->s_pipeline.pids = new int[2];
  cmd->s_pipeline.pipes = new int[4];
  cmd->s_pipeline.first_cmd = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.argv = setup_argv({"/bin/cat"});
  cmd->s_pipeline.first_cmd->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.argv = setup_argv({"/bin/ls"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next = NULL;
  test_exec(cmd, "hi friends !$\n", "", 0);
}
*/

TEST(Executor, ThreeCommandsPipeline) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->s_pipeline.pipe_count = 3;
  cmd->s_pipeline.pids = new int[3];
  cmd->s_pipeline.pipes = new int[6];
  cmd->s_pipeline.first_cmd = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.argv =
      setup_argv({"/bin/ls", "tests/test_files"});
  cmd->s_pipeline.first_cmd->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.argv = setup_argv({"/bin/cat", "-e"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next->s_command.argv =
      setup_argv({"/bin/grep", "never"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next->s_command.next = NULL;
  test_exec(cmd, "never_touch_this_file$\n", "", 0);
}

TEST(Executor, SimpleLogicalAnd) {
  t_cmd *cmd = new_cmd(LOGIC_AND);
  cmd->s_logic.left = new_cmd(COMMAND);
  cmd->s_logic.left->s_command.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->s_logic.right = new_cmd(COMMAND);
  cmd->s_logic.right->s_command.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "hi friends !\nhow are you ?\n", "", 0);
}

TEST(Executor, SimpleLogicalAndFail) {
  t_cmd *cmd = new_cmd(LOGIC_AND);
  cmd->s_logic.left = new_cmd(COMMAND);
  cmd->s_logic.left->s_command.argv = setup_argv({"/bin/bc", "not_here_file"});
  cmd->s_logic.right = new_cmd(COMMAND);
  cmd->s_logic.right->s_command.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "", "File not_here_file is unavailable.\n", 1);
}

TEST(Executor, SimpleLogicalOr) {
  t_cmd *cmd = new_cmd(LOGIC_OR);
  cmd->s_logic.left = new_cmd(COMMAND);
  cmd->s_logic.left->s_command.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->s_logic.right = new_cmd(COMMAND);
  cmd->s_logic.right->s_command.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "hi friends !\n", "", 0);
}

TEST(Executor, SimpleLogicalOrFail) {
  t_cmd *cmd = new_cmd(LOGIC_OR);
  cmd->s_logic.left = new_cmd(COMMAND);
  cmd->s_logic.left->s_command.argv = setup_argv({"/bin/bc", "not_here_file"});
  cmd->s_logic.right = new_cmd(COMMAND);
  cmd->s_logic.right->s_command.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "how are you ?\n", "File not_here_file is unavailable.\n", 0);
}

TEST(Executor, SimpleRedirIn) {
  t_cmd *cmd = new_cmd(REDIR_IN);
  cmd->s_redir.filename = (char *)strdup("tests/test_files/file_input");
  cmd->s_redir.cmd = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_command.argv = setup_argv({"/bin/cat", "-e"});
  test_exec(cmd,
            "ligne 1: ceci est la ligne 1 du file input !$\nligne 2: ligne "
            "2$\nligne 3: bon sang !$\n4 aie.$\nEOF$\n",
            "", 0);
}

TEST(Executor, RedirInAndPipe) {
  t_cmd *cmd = new_cmd(REDIR_IN);
  cmd->s_redir.filename = (char *)strdup("tests/test_files/file_input");
  cmd->s_redir.cmd = new_cmd(PIPELINE);
  cmd->s_redir.cmd->s_pipeline.pipe_count = 2;
  cmd->s_redir.cmd->s_pipeline.pids = new int[2];
  cmd->s_redir.cmd->s_pipeline.pipes = new int[4];
  cmd->s_redir.cmd->s_pipeline.first_cmd = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_pipeline.first_cmd->s_command.argv = setup_argv({"/bin/cat", "-e"});
  cmd->s_redir.cmd->s_pipeline.first_cmd->s_command.next = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_pipeline.first_cmd->s_command.next->s_command.argv =
      setup_argv({"/bin/grep", "4"});
  cmd->s_redir.cmd->s_pipeline.first_cmd->s_command.next->s_command.next = NULL;
  test_exec(cmd, "4 aie.$\n", "", 0);
}

TEST(Executor, SimpleRedirOut) {
  std::string filename = "tests/test_files/file_output";
  t_cmd *cmd = new_cmd(REDIR_OUT);
  cmd->s_redir.filename = (char *)strdup(filename.c_str());
  cmd->s_redir.cmd = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_command.argv = setup_argv({"/bin/echo", "hi friends !"});
  test_exec(cmd, "", "", 0);
  test_redir_out(filename, "hi friends !\n");
}

TEST(Executor, RedirOutWithPipe) {
  std::string filename = "tests/test_files/file_output";
  t_cmd *cmd = new_cmd(REDIR_OUT);
  cmd->s_redir.filename = (char *)strdup(filename.c_str());
  cmd->s_redir.cmd = new_cmd(PIPELINE);
  cmd->s_redir.cmd->s_pipeline.pipe_count = 2;
  cmd->s_redir.cmd->s_pipeline.pids = new int[2];
  cmd->s_redir.cmd->s_pipeline.pipes = new int[4];
  cmd->s_redir.cmd->s_pipeline.first_cmd = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_pipeline.first_cmd->s_command.argv =
      setup_argv({"/bin/echo", "hi", "friends", "!"});
  cmd->s_redir.cmd->s_pipeline.first_cmd->s_command.next = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_pipeline.first_cmd->s_command.next->s_command.argv =
      setup_argv({"/bin/tr", " ", "_"});
  cmd->s_redir.cmd->s_pipeline.first_cmd->s_command.next->s_command.next = NULL;
  test_exec(cmd, "", "", 0);
  test_redir_out(filename, "hi_friends_!\n");
}

TEST(Executor, SimpleRedirAppend) {
  std::string filename = "tests/test_files/file_output_append";
  std::ofstream file(filename);
  file << "hello world" << std::endl;
  file.close();
  t_cmd *cmd = new_cmd(REDIR_APPEND);
  cmd->s_redir.filename = (char *)strdup(filename.c_str());
  cmd->s_redir.cmd = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_command.argv = setup_argv({"/bin/echo", "hi friends !"});
  test_exec(cmd, "", "", 0);
  test_redir_out(filename, "hello world\nhi friends !\n");
  std::remove(filename.c_str());
}
