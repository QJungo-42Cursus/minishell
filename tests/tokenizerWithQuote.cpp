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
  // TODO est-ce que on crash tout de suite ?
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

TEST(TokenizeWithQuote, wordStickAfter_NotClosedQuoteNothingAfter) { //
  tokenizerTest("'word", {"'word"});
}

TEST(TokenizeWithQuote, concatenationTwoWords) {
  tokenizerTest("'hello'between'world'", {"'hello'between'world'"});
}

TEST(TokenizeWithQuote, concatenationTwoWords_whithSpaceAround) {
  tokenizerTest("    'hello'between'world'      ", {"'hello'between'world'"});
}

TEST(TokenizeWithQuote, concatenationTwoWords_whithSpaceAround_andNormalWord) {
  tokenizerTest("echo    'hello'between'world'      ",
                {"echo", "'hello'between'world'"});
}

TEST(TokenizeWithQuote, backslashAndQuote) {
  tokenizerTest("'hello\\'world'", {"'hello\\'world'"});
}

TEST(TokenizeWithQuote, others) { // TODO rename test ?
  tokenizerTest(" 'hello'between$'dollar' ", {"'hello'between$'dollar'"});
  tokenizerTest(" 'hello'between$", {"'hello'between$"});
  tokenizerTest(" 'hello'between$dollar ", {"'hello'between$dollar"});
}

/************************* TokenizeWithDoubleQuote ****************************/

TEST(TokenizeWithDoubleQuote, emptyNothingAfter) {
  tokenizerTest("word \"  \"", {"word", "\"  \""});
}

TEST(TokenizeWithDoubleQuote, notClosed) {
  tokenizerTest("word \"  ", {"word", "\"  "});
}

TEST(TokenizeWithDoubleQuote, backslashAndQuote) {
  tokenizerTest("\"hello\\\"world\"", {"\"hello\\\"world\""});
}

TEST(TokenizeWithDoubleQuote, singleWord) {
  tokenizerTest("\"word\"", {"\"word\""});
}

TEST(TokenizeWithDoubleQuote, singleWordSpaceAround) {
  tokenizerTest("  \"word\"   ", {"\"word\""});
}

TEST(TokenizeWithDoubleQuote, singleWordSpaceAroundAndInside) {
  tokenizerTest("  \"  word  \"   ", {"\"  word  \""});
}

TEST(TokenizeWithDoubleQuote, wordConcatLeft) {
  tokenizerTest("word\"  \"", {"word\"  \""});
}

TEST(TokenizeWithDoubleQuote, wordConcatRight) {
  tokenizerTest("\"  \"word", {"\"  \"word"});
}

TEST(TokenizeWithDoubleQuote, what) {
  tokenizerTest("echo \" salut\\\" \"               \"     ",
                {"echo", "\" salut\\\"", "\"               \""});
}
