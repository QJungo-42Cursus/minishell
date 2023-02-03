#include "parserAndExecutor.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <vector>

extern "C" {
#include "../executor/execute_pipeline.c"
#include "../executor/executor.c"
#include "../executor/executor.h"
#include "../executor/executor_utils.c"

#include "../builtins/cd.c"
#include "../builtins/echo.c"
#include "../builtins/exit_.c"
#include "../builtins/export.c"
#include "../builtins/pwd.c"
#include "../builtins/env.c"
#include "../builtins/unset.c"
#include "../env/get_paths_in_env.c"

#include <string.h>
}

extern "C" {
int w_exit_status(int es) { return WEXITSTATUS(es); }
}

void test_exec(t_cmd *cmd, std::string stdout_expected,
               std::string stderr_expected, int exit_status_expected) {
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();

  t_minishell *minishell;

  // int exit_status = WEXITSTATUS(execute(cmd));
  // int exit_status = (execute(cmd));
  int exit_status = w_exit_status(execute(cmd, minishell));
  std::string stdout_res = testing::internal::GetCapturedStdout();
  std::string stderr_res = testing::internal::GetCapturedStderr();

  // std::cout << stdout_res;
  // std::cout << stderr_res;

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

/* TODO les 2 qui fails avec github action mais pas en local */
TEST(Executor, aSimpleFailingPipeline) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->pipeline.pipe_count = 2;
  cmd->pipeline.pids = new int[2];
  cmd->pipeline.pipes = new int[4];
  cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.argv =
      setup_argv({"/bin/bc", "not_here_file"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
  test_exec(cmd, "", "File not_here_file is unavailable.\n", 1);
}

TEST(Executor, SimpleCommand) {
  t_cmd *cmd = new_cmd(COMMAND);
  cmd->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  test_exec(cmd, "hi friends !\n", "", 0);
}

TEST(Executor, aThreeCommandsPipelineAndFail) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->pipeline.pipe_count = 3;
  cmd->pipeline.pids = new int[3];
  cmd->pipeline.pipes = new int[6];
  cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.argv =
      setup_argv({"/bin/ls", "tests/test_files"});
  cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.argv = setup_argv({"/bin/cat", "-e"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv =
      setup_argv({"/bin/bc", "not_here_file"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.next = NULL;
  test_exec(cmd, "", "File not_here_file is unavailable.\n", 1);
}

TEST(Executor, SimpleFailingCommand) {
  t_cmd *cmd = new_cmd(COMMAND);
  cmd->cmd.argv = setup_argv({"/bin/bc", "not_here_file"});
  test_exec(cmd, "", "File not_here_file is unavailable.\n", 1);
}

TEST(Executor, SimplePipeline) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->pipeline.pipe_count = 2;
  cmd->pipeline.pids = new int[2];
  cmd->pipeline.pipes = new int[4];
  cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.argv = setup_argv({"/bin/cat", "-e"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
  test_exec(cmd, "hi friends !$\n", "", 0);
}

/*  `cat | ls`
TEST(Executor, TrickyPipeline) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->pipeline.pipe_count = 2;
  cmd->pipeline.pids = new int[2];
  cmd->pipeline.pipes = new int[4];
  cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.argv = setup_argv({"/bin/cat"});
  cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.argv = setup_argv({"/bin/ls"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
  test_exec(cmd, "hi friends !$\n", "", 0);
}
*/

TEST(Executor, ThreeCommandsPipeline) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->pipeline.pipe_count = 3;
  cmd->pipeline.pids = new int[3];
  cmd->pipeline.pipes = new int[6];
  cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.argv =
      setup_argv({"/bin/ls", "tests/test_files"});
  cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.argv = setup_argv({"/bin/cat", "-e"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv =
      setup_argv({"/bin/grep", "never"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.next = NULL;
  test_exec(cmd, "never_touch_this_file$\n", "", 0);
}

TEST(Executor, SimpleLogicalAnd) {
  t_cmd *cmd = new_cmd(LOGIC_AND);
  cmd->logic.left = new_cmd(COMMAND);
  cmd->logic.left->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->logic.right = new_cmd(COMMAND);
  cmd->logic.right->cmd.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "hi friends !\nhow are you ?\n", "", 0);
}

TEST(Executor, SimpleLogicalAndFail) {
  t_cmd *cmd = new_cmd(LOGIC_AND);
  cmd->logic.left = new_cmd(COMMAND);
  cmd->logic.left->cmd.argv = setup_argv({"/bin/bc", "not_here_file"});
  cmd->logic.right = new_cmd(COMMAND);
  cmd->logic.right->cmd.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "", "File not_here_file is unavailable.\n", 1);
}

TEST(Executor, SimpleLogicalOr) {
  t_cmd *cmd = new_cmd(LOGIC_OR);
  cmd->logic.left = new_cmd(COMMAND);
  cmd->logic.left->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->logic.right = new_cmd(COMMAND);
  cmd->logic.right->cmd.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "hi friends !\n", "", 0);
}

TEST(Executor, SimpleLogicalOrFail) {
  t_cmd *cmd = new_cmd(LOGIC_OR);
  cmd->logic.left = new_cmd(COMMAND);
  cmd->logic.left->cmd.argv = setup_argv({"/bin/bc", "not_here_file"});
  cmd->logic.right = new_cmd(COMMAND);
  cmd->logic.right->cmd.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "how are you ?\n", "File not_here_file is unavailable.\n", 0);
}

TEST(Executor, SimpleRedirIn) {
  t_cmd *cmd = new_cmd(REDIR_IN);
  cmd->redir.filename = strdup("tests/test_files/file_input");
  cmd->redir.cmd = new_cmd(COMMAND);
  cmd->redir.cmd->cmd.argv = setup_argv({"/bin/cat", "-e"});
  test_exec(cmd,
            "ligne 1: ceci est la ligne 1 du file input !$\nligne 2: ligne "
            "2$\nligne 3: bon sang !$\n4 aie.$\nEOF$\n",
            "", 0);
}

TEST(Executor, RedirInAndPipe) {
  t_cmd *cmd = new_cmd(REDIR_IN);
  cmd->redir.filename = strdup("tests/test_files/file_input");
  cmd->redir.cmd = new_cmd(PIPELINE);
  cmd->redir.cmd->pipeline.pipe_count = 2;
  cmd->redir.cmd->pipeline.pids = new int[2];
  cmd->redir.cmd->pipeline.pipes = new int[4];
  cmd->redir.cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->redir.cmd->pipeline.first_cmd->cmd.argv = setup_argv({"/bin/cat", "-e"});
  cmd->redir.cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv =
      setup_argv({"/bin/grep", "4"});
  cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
  test_exec(cmd, "4 aie.$\n", "", 0);
}

TEST(Executor, SimpleRedirOut) {
  std::string filename = "tests/test_files/file_output";
  t_cmd *cmd = new_cmd(REDIR_OUT);
  cmd->redir.filename = strdup(filename.c_str());
  cmd->redir.cmd = new_cmd(COMMAND);
  cmd->redir.cmd->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  test_exec(cmd, "", "", 0);
  test_redir_out(filename, "hi friends !\n");
}

TEST(Executor, RedirOutWithPipe) {
  std::string filename = "tests/test_files/file_output";
  t_cmd *cmd = new_cmd(REDIR_OUT);
  cmd->redir.filename = strdup(filename.c_str());
  cmd->redir.cmd = new_cmd(PIPELINE);
  cmd->redir.cmd->pipeline.pipe_count = 2;
  cmd->redir.cmd->pipeline.pids = new int[2];
  cmd->redir.cmd->pipeline.pipes = new int[4];
  cmd->redir.cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->redir.cmd->pipeline.first_cmd->cmd.argv =
      setup_argv({"/bin/echo", "hi", "friends", "!"});
  cmd->redir.cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv =
      setup_argv({"/bin/tr", " ", "_"});
  cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
  test_exec(cmd, "", "", 0);
  test_redir_out(filename, "hi_friends_!\n");
}

TEST(Executor, SimpleRedirAppend) {
  std::string filename = "tests/test_files/file_output_append";
  std::ofstream file(filename);
  file << "hello world" << std::endl;
  file.close();
  t_cmd *cmd = new_cmd(REDIR_APPEND);
  cmd->redir.filename = strdup(filename.c_str());
  cmd->redir.cmd = new_cmd(COMMAND);
  cmd->redir.cmd->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  test_exec(cmd, "", "", 0);
  test_redir_out(filename, "hello world\nhi friends !\n");
  std::remove(filename.c_str());
}
