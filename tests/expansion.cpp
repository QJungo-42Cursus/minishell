#include "gtest/gtest.h"

#include <vector>

extern "C" {
#include "../env/get_env_var_value.c"
#include "../env/get_env_var_index.c"
#include "../expansion/expansion.c"
#include "../expansion/expend_dollar.c"
#include "../expansion/get_var_position.c"
#include "../expansion/unquote.c"
#include "../minishell.h"
}

void test_expand_dollar(const char *token, int start, int end,
                        std::string expected, std::vector<std::string> env) {
  const char **env_copy = new const char *[env.size() + 1];
  for (size_t i = 0; i < env.size(); i++)
    env_copy[i] = env[i].c_str();
  env_copy[env.size()] = NULL;
  t_position token_pos = {start, end};
  char *actual = expand_dollar(token, env_copy, token_pos);
  EXPECT_STREQ(expected.c_str(), actual);
  free(actual);
}

void test_expand(const char *token, std::vector<std::string> env,
                 std::string expected) {
  const char **env_copy = new const char *[env.size() + 1];
  for (size_t i = 0; i < env.size(); i++)
    env_copy[i] = env[i].c_str();
  env_copy[env.size()] = NULL;

  const char *result = expand(token, env_copy);
  EXPECT_STREQ(expected.c_str(), result);
}

void test_get_var_position(const char *token, int begin_from,
                           int expected_start, int expected_end,
                           bool expected_found) {
  int start_index = 0;
  int end_index = 0;
  bool result =
      get_var_position(begin_from, (char *)token, &start_index, &end_index);
  EXPECT_EQ(expected_found, result);
  EXPECT_EQ(expected_start, start_index);
  EXPECT_EQ(expected_end, end_index);
}

TEST(ExpansionGetVarPosition, Simple) {
  test_get_var_position("$HOME", 0, 0, 4, true);
}

TEST(ExpansionGetVarPosition, SimpleWithSpaces) {
  test_get_var_position(" $HOME ", 0, 1, 5, true);
}

TEST(ExpansionGetVarPosition, SimpleWithSpaces2) {
  test_get_var_position(" $HOME ", 1, 1, 5, true);
}

TEST(ExpansionGetVarPosition, SimpleWithSpaces3) {
  test_get_var_position(" $HOME ", 2, 0, 0, false);
}

TEST(ExpansionGetVarPosition, FromIndex) {
  test_get_var_position("$HOME$HOME", 0, 0, 4, true);
  test_get_var_position("$HOME$HOME", 4, 5, 9, true);
}

TEST(Expansion, shouldUnquoteDquote) { test_expand("\"hello\"", {}, "hello"); }

TEST(Expansion, shouldUnquoteDquoteAndWorldAfter) {
  test_expand("\"hello\"world", {}, "helloworld");
}

TEST(Expansion, shouldUnquoteDquoteAndWorldBefore) {
  test_expand("hello\"world\"", {}, "helloworld");
}

TEST(Expansion, shouldUnquoteDquoteAndWorldBeforeAndAfter) {
  test_expand("hello\"world\"world", {}, "helloworldworld");
}

TEST(Expansion, shouldUnquoteQuote) { test_expand("'hello'", {}, "hello"); }

TEST(Expansion, shouldUnquoteQuoteAndWorldAfter) {
  test_expand("'hello'world", {}, "helloworld");
}

TEST(Expansion, shouldUnquoteQuoteAndWorldBefore) {
  test_expand("hello'world'", {}, "helloworld");
}

TEST(Expansion, shouldUnquoteQuoteAndWorldBeforeAndAfter) {
  test_expand("hello'world'world", {}, "helloworldworld");
}

TEST(DollarExpansion, Simple) {
  test_expand_dollar("$HOME", 0, 4, "/Users/alex", {"HOME=/Users/alex"});
  test_expand_dollar(" $FOO", 1, 5, " bar", {"FOO=bar"});
}

TEST(Expansion, shouldExpandHome) { //
  test_expand("$HOME", {"HOME=/home/user"}, "/home/user");
}

TEST(Expansion, shouldExpandHomeInDoubleQuotes) {
  test_expand("\"$HOME\"", {"HOME=/home/user"}, "/home/user");
}

TEST(Expansion, shouldExpandHomeInDoubleQuotesWithTextAppendBefore) {
  test_expand("maison:\"$HOME\"", {"HOME=/home/user"}, "maison:/home/user");
}

TEST(Expansion, shouldExpandHomeInDoubleQuotesWithTextAppendAfter) {
  test_expand("\"$HOME\"_isMyhouse", {"HOME=/home/user"},
              "/home/user_isMyhouse");
}

TEST(Expansion, shouldNotExpandHomeInSingleQuotes) {
  test_expand("'$HOME'", {"HOME=/home/user"}, "$HOME");
}

TEST(Expansion, doubleHome) {
  test_expand("$HOME$HOME", {"HOME=/home/user"}, "/home/user/home/user");
}

TEST(Expansion, doubleHomeAndText) {
  test_expand("maison:$HOME$HOME", {"HOME=/home/user"},
			  "maison:/home/user/home/user");
}

TEST(Expansion, doubleHomeAndText2) {
  test_expand("$HOME$HOME:maison", {"HOME=/home/user"},
			  "/home/user/home/user:maison");
}

TEST(Expansion, doubleHomeAndSpace) {
  test_expand("$HOME $HOME", {"HOME=/home/user"}, "/home/user /home/user");
}

TEST(Expansion, doubleHomeAndSpace2) {
  test_expand("$HOME$HOME $HOME", {"HOME=/home/user"},
			  "/home/user/home/user /home/user");
}

TEST(Expansion, shouldRemoveUnexistingVariable) {
  test_expand("$HOME", {}, "");
  test_expand("salut $HOME\"ca\" va ?", {"HOME="}, "salut ca va ?");
}

TEST(Expansion, shouldRemoveEmpytVariable) {
  test_expand("$HOME", {"HOME="}, "");
  //test_expand("$HOME", {"HOME"}, ""); // TODO segfault
}



