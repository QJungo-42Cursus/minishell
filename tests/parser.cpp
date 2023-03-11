#include "parserAndExecutor.hpp"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <vector>

extern "C" {
#include "../minishell.h"
}
void print_token_type(int token_type) {
  if (token_type == PIPELINE)
    std::cout << "PIPE" << std::endl;
  else if (token_type == REDIR_IN)
    std::cout << "REDIRECT_IN" << std::endl;
  else if (token_type == REDIR_OUT)
    std::cout << "REDIRECT_OUT" << std::endl;
  else if (token_type == REDIR_APPEND)
    std::cout << "REDIRECT_APPEND" << std::endl;
  else if (token_type == COMMAND)
    std::cout << "WORD" << std::endl;
}

t_list *generate_tokens(std::vector<std::string> tokens) {
  t_list *tok = NULL;

  for (std::vector<std::string>::iterator it = tokens.begin();
       it != tokens.end(); ++it) {
    ft_lstadd_back(&tok, ft_lstnew(ft_strdup((char *)it->c_str())));
  }
  return tok;
}

void compare_str_list(char **actual, char **expected) {
  int i = 0;
  while (actual[i] != NULL && expected[i] != NULL) {
    ASSERT_STREQ(actual[i], expected[i]);
    // std::cout << "actual: " << actual[i] << " expected: " << expected[i]
    //           << std::endl;
    i++;
  }
  ASSERT_EQ(actual[i], expected[i]); // check if both are NULL
}

void compare_ast(t_cmd *ast, t_cmd *expected, int depth = 0) {
  if (ast == NULL || expected == NULL)
    FAIL() << "AST is NULL at depth " << depth;
  ASSERT_EQ(ast->type, expected->type);
  if (ast->type == COMMAND) {
    compare_str_list(ast->s_command.argv, expected->s_command.argv);
    if (ast->s_command.next != NULL)
      compare_ast(ast->s_command.next, expected->s_command.next, depth + 1);
    else
      ASSERT_EQ(ast->s_command.next, expected->s_command.next);
  } else if (ast->type == PIPELINE) {
    ASSERT_EQ(ast->s_pipeline.pipe_count, expected->s_pipeline.pipe_count);
    ASSERT_NE(ast->s_pipeline.first_cmd, (t_cmd *)nullptr);
    compare_ast(ast->s_pipeline.first_cmd, expected->s_pipeline.first_cmd,
                depth + 1);
  } else if (ast->type == REDIR_IN || REDIR_OUT || REDIR_APPEND) {
    ASSERT_NE(ast->s_redir.cmd, (t_cmd *)NULL);
    // compare_ast(ast->s_redir.cmd, expected->s_redir.cmd, depth + 1);
  } else {
    FAIL() << "Invalid cmd->type at depth " << depth;
  }
}

void testParser(std::vector<std::string> tokens, t_cmd *expected,
                std::string error_exp = "") {
  if (error_exp != "") {
    testing::internal::CaptureStderr();
  }

  t_minishell *minishell = NULL;
  minishell = (t_minishell *)malloc(sizeof(t_minishell));

  t_cmd *cmd = parser(generate_tokens(tokens), minishell);
  if (error_exp != "") {
    std::string stderr_res = testing::internal::GetCapturedStderr();
    ASSERT_EQ(stderr_res, error_exp);
  } else {
    compare_ast(cmd, expected);
  }
}

/************************* ParserUtils, get_token_type ************************/

TEST(ParserUtils, get_token_type) {
  EXPECT_EQ(get_token_type((char *)"|"), PIPELINE);
  EXPECT_EQ(get_token_type((char *)">"), REDIR_OUT);
  EXPECT_EQ(get_token_type((char *)">>"), REDIR_APPEND);
  EXPECT_EQ(get_token_type((char *)"<"), REDIR_IN);
  EXPECT_EQ(get_token_type((char *)") "), COMMAND);
  EXPECT_EQ(get_token_type((char *)"ls"), COMMAND);
}

/*********************************** PARSER ***********************************/
/*********** command *********/
t_minishell *g_minishell = NULL;

TEST(ParserCmd, Simple) {
  g_minishell = (t_minishell *)malloc(sizeof(t_minishell));
  t_list *tokens = generate_tokens({"ls"});
  t_cmd *cmd = new t_cmd;
  parse_command(tokens, cmd, g_minishell);

  EXPECT_EQ(cmd->type, COMMAND);
  compare_str_list(cmd->s_command.argv, setup_argv({"ls"}));
  EXPECT_EQ(cmd->s_command.next, (t_cmd *)NULL);
}

TEST(ParserCmd, WithArgs) {
  t_list *tokens = generate_tokens({"ls", "-l", "-a"});
  t_cmd *cmd = new t_cmd;
  parse_command(tokens, cmd, g_minishell);

  EXPECT_EQ(cmd->type, COMMAND);
  compare_str_list(cmd->s_command.argv, setup_argv({"ls", "-l", "-a"}));
  EXPECT_EQ(cmd->s_command.next, (t_cmd *)NULL);
}

TEST(ParserCmd, WithManyArgs) {
  t_list *tokens = generate_tokens({"ls", "-l", "-a", "-h", "-t", "-r", "-S"});
  t_cmd *cmd = new t_cmd;
  parse_command(tokens, cmd, g_minishell);

  EXPECT_EQ(cmd->type, COMMAND);
  compare_str_list(cmd->s_command.argv,
                   setup_argv({"ls", "-l", "-a", "-h", "-t", "-r", "-S"}));
  EXPECT_EQ(cmd->s_command.next, (t_cmd *)NULL);
}

/*********** pipeline ********/
TEST(ParserPipeline, NoPipeline) {
  t_list *tokens = generate_tokens({"ls", "-l", "-a"});
  t_cmd *cmd = new t_cmd;
  ASSERT_FALSE(pipeline(tokens, cmd, g_minishell));
}

TEST(ParserPipeline, Simple) {
  t_list *tokens = generate_tokens({"ls", "|", "grep", "a"});
  t_cmd *cmd = new t_cmd;
  ASSERT_TRUE(pipeline(tokens, cmd, g_minishell));
  ASSERT_EQ(cmd->type, PIPELINE);
  ASSERT_EQ(cmd->s_pipeline.pipe_count, 2);
  ASSERT_NE(cmd->s_pipeline.first_cmd, (t_cmd *)NULL);
  ASSERT_EQ(cmd->s_pipeline.first_cmd->type, COMMAND);
  compare_str_list(cmd->s_pipeline.first_cmd->s_command.argv, setup_argv({"ls"}));
  ASSERT_NE(cmd->s_pipeline.first_cmd->s_command.next, (t_cmd *)NULL);
  ASSERT_EQ(cmd->s_pipeline.first_cmd->s_command.next->type, COMMAND);
  compare_str_list(cmd->s_pipeline.first_cmd->s_command.next->s_command.argv,
                   setup_argv({"grep", "a"}));
  EXPECT_EQ(cmd->s_pipeline.first_cmd->s_command.next->s_command.next, (t_cmd *)NULL);
}

TEST(ParserPipeline, ManyPipes) {
  t_list *tokens = generate_tokens({"ls", "|", "grep", "a", "|", "wc", "-l"});
  t_cmd *cmd = new t_cmd;
  ASSERT_TRUE(pipeline(tokens, cmd, g_minishell));
  ASSERT_EQ(cmd->type, PIPELINE);
  ASSERT_EQ(cmd->s_pipeline.pipe_count, 3);
  ASSERT_NE(cmd->s_pipeline.first_cmd, (t_cmd *)NULL);
  ASSERT_EQ(cmd->s_pipeline.first_cmd->type, COMMAND);
  compare_str_list(cmd->s_pipeline.first_cmd->s_command.argv, setup_argv({"ls"}));
  ASSERT_NE(cmd->s_pipeline.first_cmd->s_command.next, (t_cmd *)NULL);
  ASSERT_EQ(cmd->s_pipeline.first_cmd->s_command.next->type, COMMAND);
  compare_str_list(cmd->s_pipeline.first_cmd->s_command.next->s_command.argv,
                   setup_argv({"grep", "a"}));
  ASSERT_NE(cmd->s_pipeline.first_cmd->s_command.next->s_command.next, (t_cmd *)NULL);
  ASSERT_EQ(cmd->s_pipeline.first_cmd->s_command.next->s_command.next->type, COMMAND);
  compare_str_list(cmd->s_pipeline.first_cmd->s_command.next->s_command.next->s_command.argv,
                   setup_argv({"wc", "-l"}));
  EXPECT_EQ(cmd->s_pipeline.first_cmd->s_command.next->s_command.next->s_command.next,
            (t_cmd *)NULL);
}

/*********** redir ***********/
// TODO

/*********** parser **********/
TEST(Parser, EchoHello) {
  t_cmd *cmd = new_cmd(COMMAND);
  cmd->s_command.argv = setup_argv({"echo", "hello"});
  cmd->s_command.next = NULL;
  testParser({"echo", "hello"}, cmd);
}

TEST(Parser, EchoHelloWorld) {
  t_cmd *cmd = new_cmd(COMMAND);
  cmd->s_command.argv = setup_argv({"echo", "hello", "world"});
  cmd->s_command.next = NULL;
  testParser({"echo", "hello", "world"}, cmd);
}

TEST(Parser, EchoPipeCat) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->s_pipeline.pipe_count = 2;
  cmd->s_pipeline.first_cmd = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.argv = setup_argv({"echo", "hello"});
  cmd->s_pipeline.first_cmd->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.argv = setup_argv({"cat"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next = NULL;
  testParser({"echo", "hello", "|", "cat"}, cmd);
}

TEST(Parser, EchoPipeCatGrep) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->s_pipeline.pipe_count = 3;
  cmd->s_pipeline.first_cmd = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.argv = setup_argv({"echo", "hello"});
  cmd->s_pipeline.first_cmd->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.argv = setup_argv({"cat"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next = new_cmd(COMMAND);
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next->s_command.argv =
      setup_argv({"grep", "hello"});
  cmd->s_pipeline.first_cmd->s_command.next->s_command.next->s_command.next = NULL;
  testParser({"echo", "hello", "|", "cat", "|", "grep", "hello"}, cmd);
}

TEST(Parser, SimpleOutRedirection) {
  t_cmd *cmd = new_cmd(REDIR_OUT);
  cmd->s_redir.cmd = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_command.argv = setup_argv({"echo", "hello"});
  cmd->s_redir.cmd->s_command.next = NULL;
  testParser({"echo", "hello", ">", "test.txt"}, cmd);
}

TEST(Parser, SimpleInRedirection) {
  t_cmd *cmd = new_cmd(REDIR_IN);
  cmd->s_redir.cmd = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_command.argv = setup_argv({"cat"});
  cmd->s_redir.cmd->s_command.next = NULL;
  testParser({"cat", "<", "test.txt"}, cmd);
}

TEST(Parser, SimpleByRedirection) {
  t_cmd *cmd = new_cmd(REDIR_IN);
  cmd->s_redir.cmd = new_cmd(REDIR_OUT);
  cmd->s_redir.cmd->s_redir.cmd = new_cmd(COMMAND);
  cmd->s_redir.cmd->s_redir.cmd->s_command.argv = setup_argv({"cat"});
  cmd->s_redir.cmd->s_redir.cmd->s_command.next = NULL;
  testParser({"cat", "<", "test.txt", ">", "test2.txt"}, cmd);
}
