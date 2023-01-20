#include "gtest/gtest.h"
#include <vector>

extern "C" {
#include "../executor/executor.c"
#include "../executor/executor.h"
#include "../executor/executor_utils.c"
#include <string.h>
}

void test_exec(t_cmd *cmd, std::string stdout_expected,
               std::string stderr_expected, int exit_status_expected) {
  testing::internal::CaptureStdout();
  testing::internal::CaptureStderr();
  int exit_status = WEXITSTATUS(execute(cmd));
  std::string stdout_res = testing::internal::GetCapturedStdout();
  std::string stderr_res = testing::internal::GetCapturedStderr();

  std::cout << stdout_res << std::endl;
  std::cout << stderr_res << std::endl;

  EXPECT_EQ(stdout_res, stdout_expected);
  EXPECT_EQ(stderr_res, stderr_expected);
  EXPECT_EQ(exit_status, exit_status_expected);
}

char **setup_argv(std::vector<std::string> argv) {
  char **res = (char **)malloc(sizeof(char *) * (argv.size() + 1));
  for (int i = 0; i < argv.size(); i++)
    res[i] = strdup(argv[i].c_str());
  res[argv.size()] = NULL;
  return res;
}

t_cmd *new_cmd(t_cmd_type type) {
  t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
  cmd->type = type;
  return cmd;
}

TEST(Executor, SimpleCommand) {
  t_cmd *cmd = new_cmd(COMMAND);
  cmd->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  test_exec(cmd, "hi friends !\n", "", 0);
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

// TODO add failing PIPELINE
TEST(Executor, ThreeCommandsPipeline) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->pipeline.pipe_count = 3;
  cmd->pipeline.pids = new int[3];
  cmd->pipeline.pipes = new int[6];
  cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.argv =
      setup_argv({"/bin/ls", "tests/test_files", "-la"});
  cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.argv = setup_argv({"/bin/cat", "-e"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv =
      setup_argv({"/bin/grep", "never"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.next = NULL;
  test_exec(
      cmd,
      "-rw-r--r-- 1 qjungo qjungo    0 Jan 20 10:31 never_touch_this_file$\n",
      "", 0);
}

TEST(Executor, SimpleLogicalAnd) {
  t_cmd *cmd = new_cmd(LOGIC_AND);
  cmd->logic.left = new_cmd(COMMAND);
  cmd->logic.left->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->logic.right = new_cmd(COMMAND);
  cmd->logic.right->cmd.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "hi friends !\nhow are you ?\n", "", 0);
}

TEST(Executor, SimpleLogicalOr) {
  t_cmd *cmd = new_cmd(LOGIC_OR);
  cmd->logic.left = new_cmd(COMMAND);
  cmd->logic.left->cmd.argv = setup_argv({"/bin/echo", "hi friends !"});
  cmd->logic.right = new_cmd(COMMAND);
  cmd->logic.right->cmd.argv = setup_argv({"/bin/echo", "how are you ?"});
  test_exec(cmd, "hi friends !\n", "", 0);
}

// TODO add those ones

/*

t_cmd	*init_example6_redir()
{
        t_cmd *cmd = malloc(sizeof(t_cmd));
        cmd->type = REDIR_IN;
        cmd->redir.filename = strdup("test.txt");
        cmd->redir.cmd = malloc(sizeof(t_cmd));
        cmd->redir.cmd->type = PIPELINE;
        cmd->redir.cmd->pipeline.pipe_count = 2;
        cmd->redir.cmd->pipeline.pids = malloc(sizeof(int) * 2);
        cmd->redir.cmd->pipeline.pipes = malloc(sizeof(int) * 4);
        cmd->redir.cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
        cmd->redir.cmd->pipeline.first_cmd->type = COMMAND;
        cmd->redir.cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) *
3); cmd->redir.cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/cat");
        cmd->redir.cmd->pipeline.first_cmd->cmd.argv[1] = strdup("-e");
        cmd->redir.cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
        cmd->redir.cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv =
malloc(sizeof(char *) * 3);
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] =
strdup("/bin/grep"); cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] =
strdup("exe"); cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
        return (cmd);
}

t_cmd	*init_example7_redir_out()
{
        t_cmd *cmd = malloc(sizeof(t_cmd));
        cmd->type = REDIR_OUT;
        cmd->redir.filename = strdup("test2.txt");
        cmd->redir.cmd = malloc(sizeof(t_cmd));
        cmd->redir.cmd->type = PIPELINE;
        cmd->redir.cmd->pipeline.pipe_count = 2;
        cmd->redir.cmd->pipeline.pids = malloc(sizeof(int) * 2);
        cmd->redir.cmd->pipeline.pipes = malloc(sizeof(int) * 4);
        cmd->redir.cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
        cmd->redir.cmd->pipeline.first_cmd->type = COMMAND;
        cmd->redir.cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) *
3); cmd->redir.cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/echo");
        cmd->redir.cmd->pipeline.first_cmd->cmd.argv[1] = strdup("salut");
        cmd->redir.cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
        cmd->redir.cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv =
malloc(sizeof(char *) * 3);
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] =
strdup("/bin/cat"); cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] =
strdup("-e"); cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
        return (cmd);
}

t_cmd	*init_example8_redir_append()
{
        t_cmd *cmd = malloc(sizeof(t_cmd));
        cmd->type = REDIR_APPEND;
        cmd->redir.filename = strdup("test2.txt");
        cmd->redir.cmd = malloc(sizeof(t_cmd));
        cmd->redir.cmd->type = PIPELINE;
        cmd->redir.cmd->pipeline.pipe_count = 2;
        cmd->redir.cmd->pipeline.pids = malloc(sizeof(int) * 2);
        cmd->redir.cmd->pipeline.pipes = malloc(sizeof(int) * 4);
        cmd->redir.cmd->pipeline.first_cmd = malloc(sizeof(t_cmd));
        cmd->redir.cmd->pipeline.first_cmd->type = COMMAND;
        cmd->redir.cmd->pipeline.first_cmd->cmd.argv = malloc(sizeof(char *) *
3); cmd->redir.cmd->pipeline.first_cmd->cmd.argv[0] = strdup("/bin/echo");
        cmd->redir.cmd->pipeline.first_cmd->cmd.argv[1] = strdup("salut
append"); cmd->redir.cmd->pipeline.first_cmd->cmd.argv[2] = NULL;
        cmd->redir.cmd->pipeline.first_cmd->cmd.next = malloc(sizeof(t_cmd));
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->type = COMMAND;
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv =
malloc(sizeof(char *) * 3);
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[0] =
strdup("/bin/cat"); cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[1] =
strdup("-e"); cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.argv[2] = NULL;
        cmd->redir.cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
        return (cmd);
}
*/
