#include "gtest/gtest.h"
#include <iostream>

extern "C" {
// libft
#include "../libft/libft.h"
// all needed C files
#include "../tokenizer/debug_helpers.c"
#include "../tokenizer/get_next_token_functions.c"
#include "../tokenizer/get_token_dquote.c"
#include "../tokenizer/get_token_normal.c"
#include "../tokenizer/get_token_quote.c"
#include "../tokenizer/get_token_redirect.c"
#include "../tokenizer/tokenizer.c"
}

/***************************** Tokenize ***************************************/

TEST(Tokenize, whiteSpaceBetweenWordsAndEndAndStart) {
  const char *sentence = "   ls   -l   ";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, whiteSpaceBetweenWords) {
  const char *sentence = "ls -l";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, singleWord) {
  const char *sentence = "word";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "word");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, oneAmpersant) {
  const char *sentence = "ls -l &";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, "&");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, twoAmpersant) {
  const char *sentence = "ls -l && cat";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, "&&");
  EXPECT_STREQ((char *)tokens->next->next->next->content, "cat");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, onePipe) {
  const char *sentence = "ls -l |";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, "|");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, twoPipe) {
  const char *sentence = "ls -l || cat";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, "||");
  EXPECT_STREQ((char *)tokens->next->next->next->content, "cat");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, oneAmpersantAndOnePipe) {
  // TODO ?
  const char *sentence = "ls -l & |";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, "&");
  EXPECT_STREQ((char *)tokens->next->next->next->content, "|");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, oneArrowLeft) {
  const char *sentence = "ls -l < cat";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, "<");
  EXPECT_STREQ((char *)tokens->next->next->next->content, "cat");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, twoArrowLeft) {
  const char *sentence = "ls -l << cat";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, "<<");
  EXPECT_STREQ((char *)tokens->next->next->next->content, "cat");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, oneArrowRight) {
  const char *sentence = "ls -l > cat";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, ">");
  EXPECT_STREQ((char *)tokens->next->next->next->content, "cat");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, twoArrowRight) {
  const char *sentence = "ls -l >> cat";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, ">>");
  EXPECT_STREQ((char *)tokens->next->next->next->content, "cat");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, oneArrowRightAndOneArrowLeft) {
  const char *sentence = "ls -l > cat < cat";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, ">");
  EXPECT_STREQ((char *)tokens->next->next->next->content, "cat");
  EXPECT_STREQ((char *)tokens->next->next->next->next->content, "<");
  EXPECT_STREQ((char *)tokens->next->next->next->next->next->content, "cat");
  ft_lstclear(&tokens, free);
}

TEST(Tokenize, oneArrowRightAndOneArrowLeftAndOnePipe) {
  const char *sentence = "ls -l > cat < cat |";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "ls");
  EXPECT_STREQ((char *)tokens->next->content, "-l");
  EXPECT_STREQ((char *)tokens->next->next->content, ">");
  EXPECT_STREQ((char *)tokens->next->next->next->content, "cat");
  EXPECT_STREQ((char *)tokens->next->next->next->next->content, "<");
  EXPECT_STREQ((char *)tokens->next->next->next->next->next->content, "cat");
  EXPECT_STREQ((char *)tokens->next->next->next->next->next->next->content,
               "|");
  ft_lstclear(&tokens, free);
}

// TODO add :
// 2>
// copilot propose :
// 2>>
// 2>&1
// 2>&-
// 2>&1

TEST(Tokenize, what) {
  FAIL() << "segfault";
  const char *sentence = "echo \" salut\\\" \"               \"     ";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "echo");
  EXPECT_STREQ((char *)tokens->next->content, " salut\\\" ");
  EXPECT_STREQ((char *)tokens->next->next->content, "     ");
  ft_lstclear(&tokens, free);
}

/***************************** TokenizeWithQuote ******************************/

TEST(TokenizeWithQuote, backslashAndQuote) {
  FAIL() << "segfault";
  t_list *tokens = tokenizer("'hello\'world'");
  EXPECT_STREQ((char *)tokens->content, "echo");
  EXPECT_STREQ((char *)tokens->next->content, "hello\\'world");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithQuote, singleWord) {
  FAIL() << "segfault";
  const char *sentence = "'word'";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "'word'");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithQuote, singleWordSpaceAround) {
  FAIL() << "segfault";
  const char *sentence = "  'word'   ";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "'word'");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithQuote, singleWordSpaceAroundAndInside) {
  FAIL() << "segfault";
  const char *sentence = "  '  word  '   ";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "'word'");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithQuote, emptyNothingAfter) {
  FAIL() << "segfault";
  const char *sentence = "word '  '";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "word");
  // TODO sur de ca ?
  EXPECT_STREQ((char *)tokens->next->content, "'  '");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithQuote, notClosed) {
  FAIL() << "segfault";
  const char *sentence = "word '  ";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "word");
  // TODO gerer ca comme une erreure ? Pas selon la consigne
  EXPECT_STREQ((char *)tokens->next->content, "'  ");
  ft_lstclear(&tokens, free);
}

/************************* TokenizeWithDoubleQuote ****************************/

// TODO bien verifier comment bash gere les backslash

TEST(TokenizeWithDoubleQuote, emptyNothingAfter) {
  FAIL() << "segfault";
  const char *sentence = "word \"  \"";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "word");
  // TODO sur de ca ?
  EXPECT_STREQ((char *)tokens->next->content, "\"  \"");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithDoubleQuote, notClosed) {
  FAIL() << "segfault";
  const char *sentence = "word \"  ";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "word");
  // TODO gerer ca comme une erreure ? Pas selon la consigne
  EXPECT_STREQ((char *)tokens->next->content, "\"  ");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithDoubleQuote, backslashAndQuote) {
  FAIL() << "segfault";
  t_list *tokens = tokenizer("\"hello\\\"world\"");
  EXPECT_STREQ((char *)tokens->content, "echo");
  EXPECT_STREQ((char *)tokens->next->content, "hello\\\"world");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithDoubleQuote, singleWord) {
  FAIL() << "segfault";
  const char *sentence = "\"word\"";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "\"word\"");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithDoubleQuote, singleWordSpaceAround) {
  FAIL() << "segfault";
  const char *sentence = "  \"word\"   ";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "\"word\"");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithDoubleQuote, singleWordSpaceAroundAndInside) {
  FAIL() << "segfault";
  const char *sentence = "  \"  word  \"   ";
  t_list *tokens = tokenizer(sentence);
  // TODO ?
  EXPECT_STREQ((char *)tokens->content, "\"word\"");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithDoubleQuote, wordConcatLeft) {
  FAIL() << "segfault";
  const char *sentence = "word\"  \"";
  t_list *tokens = tokenizer(sentence);
  // TODO ?
  EXPECT_STREQ((char *)tokens->content, "word");
  EXPECT_STREQ((char *)tokens->next->content, "\"  \"");
  ft_lstclear(&tokens, free);
}

TEST(TokenizeWithDoubleQuote, wordConcatRight) {
  FAIL() << "segfault";
  const char *sentence = "\"  \"word";
  t_list *tokens = tokenizer(sentence);
  // TODO ?
  EXPECT_STREQ((char *)tokens->content, "\"  \"");
  EXPECT_STREQ((char *)tokens->next->content, "word");
  ft_lstclear(&tokens, free);
}
