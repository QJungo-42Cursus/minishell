#include "parserAndExecutor.h"
#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <vector>

extern "C" {
#include "../libft/libft.h"
#include "../parser/parse_command.c"
#include "../parser/parse_pipeline.c"
#include "../parser/parser.c"
#include "../parser/parser.h"
#include "../parser/parser_utils.c"
#include <stdio.h>
#include <stdlib.h>
}

void print_token_type(int token_type) {
  if (token_type == OPEN_PARENTHESES)
    std::cout << "OPEN_PARENTHESES" << std::endl;
  else if (token_type == CLOSE_PARENTHESES)
    std::cout << "CLOSE_PARENTHESES" << std::endl;
  else if (token_type == PIPELINE)
    std::cout << "PIPE" << std::endl;
  else if (token_type == LOGIC_AND)
    std::cout << "AND" << std::endl;
  else if (token_type == LOGIC_OR)
    std::cout << "OR" << std::endl;
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
    compare_str_list(ast->cmd.argv, expected->cmd.argv);
    if (ast->cmd.next != NULL)
      compare_ast(ast->cmd.next, expected->cmd.next, depth + 1);
    else
      ASSERT_EQ(ast->cmd.next, expected->cmd.next);
  } else if (ast->type == PIPELINE) {
    ASSERT_EQ(ast->pipeline.pipe_count, expected->pipeline.pipe_count);
    ASSERT_NE(ast->pipeline.first_cmd, (t_cmd *)nullptr);
    compare_ast(ast->pipeline.first_cmd, expected->pipeline.first_cmd,
                depth + 1);
  } else if (ast->type == LOGIC_AND || ast->type == LOGIC_OR) {
    ASSERT_NE(ast->pipe.left, (t_cmd *)NULL);
    ASSERT_NE(ast->pipe.right, (t_cmd *)NULL);
    compare_ast(ast->pipe.left, expected->pipe.left, depth + 1);
    compare_ast(ast->pipe.right, expected->pipe.right, depth + 1);
  } else if (ast->type == REDIR_IN || REDIR_OUT || REDIR_APPEND) {
    ASSERT_STREQ(ast->redir.filename, expected->redir.filename);
    ASSERT_NE(ast->redir.cmd, (t_cmd *)NULL);
    // compare_ast(ast->redir.cmd, expected->redir.cmd, depth + 1);
  } else {
    FAIL() << "Invalid cmd->type at depth " << depth;
  }
}

void testParser(std::vector<std::string> tokens, t_cmd *expected,
                std::string error_exp = "") {
  if (error_exp != "")
    testing::internal::CaptureStderr();
  t_cmd *cmd = parser(generate_tokens(tokens));
  if (error_exp != "") {
    std::string stderr_res = testing::internal::GetCapturedStderr();
    ASSERT_EQ(stderr_res, error_exp);
  } else {
    compare_ast(cmd, expected);
  }
}

/************************* ParserUtils, get_token_type ************************/

TEST(ParserUtils, get_token_type) {
  EXPECT_EQ(get_token_type((char *)"&&"), LOGIC_AND);
  EXPECT_EQ(get_token_type((char *)"||"), LOGIC_OR);
  EXPECT_EQ(get_token_type((char *)"|"), PIPELINE);
  EXPECT_EQ(get_token_type((char *)">"), REDIR_OUT);
  EXPECT_EQ(get_token_type((char *)">>"), REDIR_APPEND);
  EXPECT_EQ(get_token_type((char *)"<"), REDIR_IN);
  EXPECT_EQ(get_token_type((char *)"("), OPEN_PARENTHESES);
  EXPECT_EQ(get_token_type((char *)")"), CLOSE_PARENTHESES);

  EXPECT_EQ(get_token_type((char *)") "), COMMAND);
  EXPECT_EQ(get_token_type((char *)"ls"), COMMAND);
}

/****************** ParserUtils, are_we_in_parentheses ************************/

TEST(ParserUtils, are_we_in_parentheses_SimpleTrue) {
  t_list *tok = generate_tokens({"(", "&&", "ls", "echo", "hello", ")"});
  EXPECT_EQ(are_we_in_parentheses(tok), true);
}

TEST(ParserUtils, are_we_in_parentheses_SimpleFalse) {
  t_list *tok = generate_tokens({"ls", "&&", "echo", "hello"});
  EXPECT_EQ(are_we_in_parentheses(tok), false);
}

TEST(ParserUtils, are_we_in_parentheses_TrickyTrue) {
  t_list *tok = generate_tokens({"(",                             //
                                 "ls", "&&",                      //
                                 "(", "echo", "hello", ")", "||", //
                                 "(", "echo", "world", ")",       //
                                 ")"});
  EXPECT_EQ(are_we_in_parentheses(tok), true);
}

TEST(ParserUtils, are_we_in_parentheses_TrickyFalse) {
  t_list *tok = generate_tokens({"ls", "&&", "(", "echo", "hello", ")", "||",
                                 "(", "echo", "world", ")", ")"});
  EXPECT_EQ(are_we_in_parentheses(tok), false);
}

TEST(ParserUtils, are_we_in_parentheses_RandomTrue) {
  t_list *tok = generate_tokens({"(", "ls", "&&", "(", "echo", "hello", ")"});
  // TODO ca devrait etre une erreur
  EXPECT_EQ(are_we_in_parentheses(tok), false);
}

/********************** ParserUtils, skip_parentheses *************************/

void test_skip_parentheses(std::vector<std::string> tokens, int expected) {
  t_list *tok = generate_tokens(tokens);
  t_list *new_tok = skip_parentheses(tok);
  for (int i = 0; i < expected && new_tok != NULL; i++) {
    tok = tok->next;
  }
  EXPECT_EQ(new_tok, tok);
  EXPECT_STREQ((char *)new_tok->content, (char *)tok->content);
}

TEST(ParserUtils, skip_parentheses_Simple) {
  test_skip_parentheses(
      {"(", "ls", "&&", "(", "echo", "hello", ")", ")", "&&", "echo", "world"},
      7);
}

TEST(ParserUtils, skip_parentheses_NoParentheses) {
  test_skip_parentheses(
      {"ls", "&&", "(", "echo", "hello", ")", "&&", "echo", "world"}, 0);
}

/******************* ParserUtils, lst_cut_first_and_last **********************/

TEST(ParserUtils, lst_cut_first_and_last_Simple) {
  t_list *tok = generate_tokens({"(", "echo", "hello", ")"});
  t_list *new_tok = lst_cut_first_and_last(tok);
  EXPECT_EQ(new_tok, tok->next);
  EXPECT_STREQ((char *)new_tok->content, (char *)tok->next->content);
  tok = tok->next;
  while (new_tok->next != NULL) {
    // std::cout << (char *)tok->content << std::endl;
    tok = tok->next;
    new_tok = new_tok->next;
    EXPECT_STREQ((char *)new_tok->content, (char *)tok->content);
  }
  // std::cout << (char *)new_tok->content << std::endl;
  EXPECT_EQ(new_tok, tok);
}

/*********************************** PARSER ***********************************/
/*********** command *********/
TEST(ParserCmd, Simple) {
  t_list *tokens = generate_tokens({"ls"});
  t_cmd *cmd = new t_cmd;
  parse_command(tokens, cmd);

  EXPECT_EQ(cmd->type, COMMAND);
  compare_str_list(cmd->cmd.argv, setup_argv({"ls"}));
  EXPECT_EQ(cmd->cmd.next, (t_cmd *)NULL);
}

TEST(ParserCmd, WithArgs) {
  t_list *tokens = generate_tokens({"ls", "-l", "-a"});
  t_cmd *cmd = new t_cmd;
  parse_command(tokens, cmd);

  EXPECT_EQ(cmd->type, COMMAND);
  compare_str_list(cmd->cmd.argv, setup_argv({"ls", "-l", "-a"}));
  EXPECT_EQ(cmd->cmd.next, (t_cmd *)NULL);
}

TEST(ParserCmd, WithManyArgs) {
  t_list *tokens = generate_tokens({"ls", "-l", "-a", "-h", "-t", "-r", "-S"});
  t_cmd *cmd = new t_cmd;
  parse_command(tokens, cmd);

  EXPECT_EQ(cmd->type, COMMAND);
  compare_str_list(cmd->cmd.argv,
                   setup_argv({"ls", "-l", "-a", "-h", "-t", "-r", "-S"}));
  EXPECT_EQ(cmd->cmd.next, (t_cmd *)NULL);
}

TEST(ParserCmd, SimpleParentesesError) {

  t_list *tokens = generate_tokens({"echo", "(", "ls", ")"});
  t_cmd *cmd = new t_cmd;
  std::string expected = "minishell: syntax error near unexpected token `ls'\n";
  testing::internal::CaptureStderr();
  parse_command(tokens, cmd);
  std::string stderr_res = testing::internal::GetCapturedStderr();
  EXPECT_EQ(stderr_res, expected);
}

TEST(ParserCmd, RightParentesesError) {
  t_list *tokens = generate_tokens({"echo", "ls", ")"});
  t_cmd *cmd = new t_cmd;
  std::string expected = "minishell: syntax error near unexpected token `)'\n";
  testing::internal::CaptureStderr();
  parse_command(tokens, cmd);
  std::string stderr_res = testing::internal::GetCapturedStderr();
  EXPECT_EQ(stderr_res, expected);
}

/*********** pipeline ********/
TEST(ParserPipeline, NoPipeline) {
  t_list *tokens = generate_tokens({"ls", "-l", "-a"});
  t_cmd *cmd = new t_cmd;
  ASSERT_FALSE(pipeline(tokens, cmd));
}

TEST(ParserPipeline, Simple) {
  t_list *tokens = generate_tokens({"ls", "|", "grep", "a"});
  t_cmd *cmd = new t_cmd;
  ASSERT_TRUE(pipeline(tokens, cmd));
  ASSERT_EQ(cmd->type, PIPELINE);
  ASSERT_EQ(cmd->pipeline.pipe_count, 2);
  ASSERT_NE(cmd->pipeline.first_cmd, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->type, COMMAND);
  compare_str_list(cmd->pipeline.first_cmd->cmd.argv, setup_argv({"ls"}));
  ASSERT_NE(cmd->pipeline.first_cmd->cmd.next, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->type, COMMAND);
  compare_str_list(cmd->pipeline.first_cmd->cmd.next->cmd.argv,
                   setup_argv({"grep", "a"}));
  EXPECT_EQ(cmd->pipeline.first_cmd->cmd.next->cmd.next, (t_cmd *)NULL);
}

TEST(ParserPipeline, ManyPipes) {
  t_list *tokens = generate_tokens({"ls", "|", "grep", "a", "|", "wc", "-l"});
  t_cmd *cmd = new t_cmd;
  ASSERT_TRUE(pipeline(tokens, cmd));
  ASSERT_EQ(cmd->type, PIPELINE);
  ASSERT_EQ(cmd->pipeline.pipe_count, 3);
  ASSERT_NE(cmd->pipeline.first_cmd, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->type, COMMAND);
  compare_str_list(cmd->pipeline.first_cmd->cmd.argv, setup_argv({"ls"}));
  ASSERT_NE(cmd->pipeline.first_cmd->cmd.next, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->type, COMMAND);
  compare_str_list(cmd->pipeline.first_cmd->cmd.next->cmd.argv,
                   setup_argv({"grep", "a"}));
  ASSERT_NE(cmd->pipeline.first_cmd->cmd.next->cmd.next, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->cmd.next->type, COMMAND);
  compare_str_list(cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv,
                   setup_argv({"wc", "-l"}));
  EXPECT_EQ(cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.next,
            (t_cmd *)NULL);
}

TEST(ParserPipeline, PipelinesAndParenteses) {
  // TODO - est-ce qu'on veut vraiment que le dernier noeud de la liste de cmd
  // d'une pipe puisse etre autre chose qu'une commande ?
  // Dans le cas ci-dessous, le dernier est un 2eme pipeline,
  // a cause des parenteses
  t_list *tokens = generate_tokens(
      {"ls", "|", "wc", "-l", "|", "(", "grep", "a", "|", "cat", ")"});
  t_cmd *cmd = new t_cmd;
  ASSERT_TRUE(pipeline(tokens, cmd));
  ASSERT_EQ(cmd->type, PIPELINE);
  ASSERT_EQ(cmd->pipeline.pipe_count, 3);
  ASSERT_NE(cmd->pipeline.first_cmd, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->type, COMMAND);
  compare_str_list(cmd->pipeline.first_cmd->cmd.argv, setup_argv({"ls"}));
  ASSERT_NE(cmd->pipeline.first_cmd->cmd.next, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->type, COMMAND);
  compare_str_list(cmd->pipeline.first_cmd->cmd.next->cmd.argv,
                   setup_argv({"wc", "-l"}));
  ASSERT_NE(cmd->pipeline.first_cmd->cmd.next->cmd.next, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->cmd.next->type, PIPELINE);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->cmd.next->pipeline.pipe_count,
            2);
  ASSERT_NE(cmd->pipeline.first_cmd->cmd.next->cmd.next->pipeline.first_cmd,
            (t_cmd *)NULL);
  ASSERT_EQ(
      cmd->pipeline.first_cmd->cmd.next->cmd.next->pipeline.first_cmd->type,
      COMMAND);
  compare_str_list(
      cmd->pipeline.first_cmd->cmd.next->cmd.next->pipeline.first_cmd->cmd.argv,
      setup_argv({"grep", "a"}));
  ASSERT_NE(
      cmd->pipeline.first_cmd->cmd.next->cmd.next->pipeline.first_cmd->cmd.next,
      (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->cmd.next->pipeline.first_cmd->cmd
                .next->type,
            COMMAND);
  compare_str_list(cmd->pipeline.first_cmd->cmd.next->cmd.next->pipeline
                       .first_cmd->cmd.next->cmd.argv,
                   setup_argv({"cat"}));
  EXPECT_EQ(cmd->pipeline.first_cmd->cmd.next->cmd.next->pipeline.first_cmd->cmd
                .next->cmd.next,
            (t_cmd *)NULL);
}

TEST(ParserPipeline, PipelinesAndParenteses2) {
  t_list *tokens = generate_tokens({"(", "ls", "|", "wc", "-l", ")", "|", "(",
                                    "grep", "a", "|", "cat", ")"});
  t_cmd *cmd = new t_cmd;
  ASSERT_TRUE(pipeline(tokens, cmd));
  ASSERT_EQ(cmd->type, PIPELINE);
  ASSERT_EQ(cmd->pipeline.pipe_count, 2);
  ASSERT_NE(cmd->pipeline.first_cmd, (t_cmd *)NULL);

  ASSERT_EQ(cmd->pipeline.first_cmd->type, PIPELINE);
  ASSERT_EQ(cmd->pipeline.first_cmd->pipeline.pipe_count, 2);
  ASSERT_NE(cmd->pipeline.first_cmd->pipeline.first_cmd, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->pipeline.first_cmd->type, COMMAND);
  compare_str_list(cmd->pipeline.first_cmd->pipeline.first_cmd->cmd.argv,
                   setup_argv({"ls"}));
  ASSERT_NE(cmd->pipeline.first_cmd->pipeline.first_cmd->cmd.next,
            (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->pipeline.first_cmd->cmd.next->type,
            COMMAND);
  compare_str_list(
      cmd->pipeline.first_cmd->pipeline.first_cmd->cmd.next->cmd.argv,
      setup_argv({"wc", "-l"}));
  EXPECT_EQ(cmd->pipeline.first_cmd->pipeline.first_cmd->cmd.next->cmd.next,
            (t_cmd *)NULL);

  ASSERT_NE(cmd->pipeline.first_cmd->cmd.next, (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->type, PIPELINE);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->pipeline.pipe_count, 2);
  ASSERT_NE(cmd->pipeline.first_cmd->cmd.next->pipeline.first_cmd,
            (t_cmd *)NULL);
  ASSERT_EQ(cmd->pipeline.first_cmd->cmd.next->pipeline.first_cmd->type,
            COMMAND);
  compare_str_list(
      cmd->pipeline.first_cmd->cmd.next->pipeline.first_cmd->cmd.argv,
      setup_argv({"grep", "a"}));
  ASSERT_NE(cmd->pipeline.first_cmd->cmd.next->pipeline.first_cmd->cmd.next,
            (t_cmd *)NULL);
  ASSERT_EQ(
      cmd->pipeline.first_cmd->cmd.next->pipeline.first_cmd->cmd.next->type,
      COMMAND);
  compare_str_list(
      cmd->pipeline.first_cmd->cmd.next->pipeline.first_cmd->cmd.next->cmd.argv,
      setup_argv({"cat"}));
  EXPECT_EQ(
      cmd->pipeline.first_cmd->cmd.next->pipeline.first_cmd->cmd.next->cmd.next,
      (t_cmd *)NULL);
}

/*********** redir ***********/
/*********** logic ***********/
TEST(ParserLogic, NoLogic) {
  std::vector<std::string> tokens = {"ls", "echo", "hello"};
  t_cmd *cmd = new t_cmd;
  bool result = logic(generate_tokens(tokens), cmd);
  EXPECT_EQ(result, false);
}

/*********** parser **********/
TEST(Parser, EchoHello) {
  t_cmd *cmd = new_cmd(COMMAND);
  cmd->cmd.argv = setup_argv({"echo", "hello"});
  cmd->cmd.next = NULL;
  testParser({"echo", "hello"}, cmd);
}

TEST(Parser, EchoHelloWorld) {
  t_cmd *cmd = new_cmd(COMMAND);
  cmd->cmd.argv = setup_argv({"echo", "hello", "world"});
  cmd->cmd.next = NULL;
  testParser({"echo", "hello", "world"}, cmd);
}

TEST(Parser, FailParentheses) {
  testParser({"echo", "hello", "world", ")"}, NULL,
             "minishell: syntax error near unexpected token `)'\n");
}

TEST(Parser, FailParentheses2) {
  testParser({"echo", "hello", "world", "(", "ls", ")"}, NULL,
             "minishell: syntax error near unexpected token `ls'\n");
}

TEST(Parser, FailParentheses3) {
  testParser({"world", "(", "ls", "d"}, NULL,
             "minishell: syntax error near unexpected token `ls'\n");
}

TEST(Parser, EchoPipeCat) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->pipeline.pipe_count = 2;
  cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.argv = setup_argv({"echo", "hello"});
  cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.argv = setup_argv({"cat"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next = NULL;
  testParser({"echo", "hello", "|", "cat"}, cmd);
}

TEST(Parser, EchoPipeCatGrep) {
  t_cmd *cmd = new_cmd(PIPELINE);
  cmd->pipeline.pipe_count = 3;
  cmd->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.argv = setup_argv({"echo", "hello"});
  cmd->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.argv = setup_argv({"cat"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next = new_cmd(COMMAND);
  cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.argv =
      setup_argv({"grep", "hello"});
  cmd->pipeline.first_cmd->cmd.next->cmd.next->cmd.next = NULL;
  testParser({"echo", "hello", "|", "cat", "|", "grep", "hello"}, cmd);
}

TEST(Parser, LogicAndPipeline) {
  t_cmd *cmd = new_cmd(LOGIC_AND);
  cmd->logic.left = new_cmd(PIPELINE);
  cmd->logic.left->pipeline.pipe_count = 2;
  cmd->logic.left->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->logic.left->pipeline.first_cmd->cmd.argv = setup_argv({"echo", "hello"});
  cmd->logic.left->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->logic.left->pipeline.first_cmd->cmd.next->cmd.argv = setup_argv({"cat"});
  cmd->logic.left->pipeline.first_cmd->cmd.next->cmd.next = NULL;
  cmd->logic.right = new_cmd(COMMAND);
  cmd->logic.right->cmd.argv = setup_argv({"echo", "hello"});
  cmd->logic.right->cmd.next = NULL;
  testParser({"echo", "hello", "|", "cat", "&&", "echo", "hello"}, cmd);
}

TEST(Parser, LogicAndPipelineInParentheses) {
  t_cmd *cmd = new_cmd(LOGIC_AND);
  cmd->logic.left = new_cmd(PIPELINE);
  cmd->logic.left->pipeline.pipe_count = 2;
  cmd->logic.left->pipeline.first_cmd = new_cmd(COMMAND);
  cmd->logic.left->pipeline.first_cmd->cmd.argv = setup_argv({"echo", "hello"});
  cmd->logic.left->pipeline.first_cmd->cmd.next = new_cmd(COMMAND);
  cmd->logic.left->pipeline.first_cmd->cmd.next->cmd.argv = setup_argv({"cat"});
  cmd->logic.left->pipeline.first_cmd->cmd.next->cmd.next = NULL;
  cmd->logic.right = new_cmd(COMMAND);
  cmd->logic.right->cmd.argv = setup_argv({"echo", "hello"});
  cmd->logic.right->cmd.next = NULL;
  testParser(
      {"(", "echo", "hello", "|", "cat", ")", "&&", "(", "echo", "hello", ")"},
      cmd);
}

TEST(Parser, SimpleOutRedirection) {
  t_cmd *cmd = new_cmd(REDIR_OUT);
  cmd->redir.cmd = new_cmd(COMMAND);
  cmd->redir.filename = (char *)"test.txt";
  cmd->redir.cmd->cmd.argv = setup_argv({"echo", "hello"});
  cmd->redir.cmd->cmd.next = NULL;
  testParser({"echo", "hello", ">", "test.txt"}, cmd);
}

TEST(Parser, SimpleInRedirection) {
  t_cmd *cmd = new_cmd(REDIR_IN);
  cmd->redir.cmd = new_cmd(COMMAND);
  cmd->redir.filename = (char *)"test.txt";
  cmd->redir.cmd->cmd.argv = setup_argv({"cat"});
  cmd->redir.cmd->cmd.next = NULL;
  testParser({"cat", "<", "test.txt"}, cmd);
}

TEST(Parser, SimpleByRedirection) {
  t_cmd *cmd = new_cmd(REDIR_IN);
  cmd->redir.cmd = new_cmd(REDIR_OUT);
  cmd->redir.filename = (char *)"test.txt";
  cmd->redir.cmd->redir.cmd = new_cmd(COMMAND);
  cmd->redir.cmd->redir.filename = (char *)"test2.txt";
  cmd->redir.cmd->redir.cmd->cmd.argv = setup_argv({"cat"});
  cmd->redir.cmd->redir.cmd->cmd.next = NULL;
  testParser({"cat", "<", "test.txt", ">", "test2.txt"}, cmd);
}

// TODO add all exeptions (like with parenthesis)
