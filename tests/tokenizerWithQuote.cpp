extern "C" {
#include "../libft/libft.h"
t_list *tokenizer(const char *str);
}
#include "gtest/gtest.h"
void tokenizerTest(const char *sentence, std::vector<std::string> expected);

/***************************** TokenizeWithQuote ******************************/

TEST(TokenizeWithQuote, singleWord) { //
  tokenizerTest("'word'", {"'word'"});
}

TEST(TokenizeWithQuote, singleWordAndOneWithoutQuoteFront) {
  tokenizerTest("echo 'word'", {"echo", "'word'"});
}

TEST(TokenizeWithQuote, singleWordSpaceAround) {
  tokenizerTest("  'word'   ", {"'word'"});
}

TEST(TokenizeWithQuote, singleWordSpaceAroundAndInside) {
  tokenizerTest("  '  word  '   ", {"'  word  '"});
}

TEST(TokenizeWithQuote, someSpaceNothingAfter) {
  tokenizerTest("word '  '", {"word", "'  '"});
}

TEST(TokenizeWithQuote, notClosedWithSpaceAfter) { //
  tokenizerTest("word '  ", {"word", "'  "});
}

TEST(TokenizeWithQuote, notClosedWithDollarAfter) { //
  tokenizerTest("word '  $", {"word", "'  $"});
}

TEST(TokenizeWithQuote, notClosedNothingAfter) { //
  tokenizerTest("word '", {"word", "'"});
}

TEST(TokenizeWithQuote, justOneQuote) { //
  tokenizerTest("'", {"'"});
}

TEST(TokenizeWithQuote, wordStickAfter) {
  tokenizerTest("'hello'word", {"'hello'word"});
}

TEST(TokenizeWithQuote, wordStickBefore) { //
  tokenizerTest("word'hello'", {"word'hello'"});
}

TEST(TokenizeWithQuote, wordStickBefore_NotClosedQuoteNothingAfter) { //
  tokenizerTest("word'", {"word'"});
}

TEST(TokenizeWithQuote, backslashAndQuote) {
  tokenizerTest("'hello\\'world'", {"'hello\\'world'"});
}

/************************* TokenizeWithDoubleQuote ****************************/

// TODO bien verifier comment bash gere les backslash

/*
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
*/

/*
TEST(Tokenize, what) {
  FAIL() << "segfault";
  const char *sentence = "echo \" salut\\\" \"               \"     ";
  t_list *tokens = tokenizer(sentence);
  EXPECT_STREQ((char *)tokens->content, "echo");
  EXPECT_STREQ((char *)tokens->next->content, " salut\\\" ");
  EXPECT_STREQ((char *)tokens->next->next->content, "     ");
  ft_lstclear(&tokens, free);
}
*/
