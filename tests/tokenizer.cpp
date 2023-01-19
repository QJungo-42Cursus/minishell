#include "gtest/gtest.h"
#include <array>
#include <iostream>

extern "C" {
#include "../libft/libft.h"
t_list *tokenizer(const char *str);
}

void tokenizerTest(const char *sentence, std::vector<std::string> expected) {
  t_list *tokens = tokenizer(sentence);
  t_list *current = tokens;
  for (size_t i = 0; i < expected.size(); i++) {
    EXPECT_EQ(std::string((char *)current->content), expected[i]);
    current = current->next;
  }
  EXPECT_EQ(current, nullptr);
  ft_lstclear(&tokens, free);
}

/***************************** Tokenize ***************************************/

TEST(Tokenize, singleWord) { //
  tokenizerTest("word", {"word"});
}

TEST(Tokenize, whiteSpaceBetweenWords) { //
  tokenizerTest("ls -l", {"ls", "-l"});
}

TEST(Tokenize, whiteSpaceBetweenWordsAndEndAndStart) {
  tokenizerTest("   ls   -l   ", {"ls", "-l"});
}

TEST(Tokenize, oneAmpersant) { //
  tokenizerTest("ls -l &", {"ls", "-l", "&"});
}

TEST(Tokenize, twoAmpersant) {
  tokenizerTest("ls -l && cat", {"ls", "-l", "&&", "cat"});
}

TEST(Tokenize, onePipe) { //
  tokenizerTest("ls -l |", {"ls", "-l", "|"});
}

TEST(Tokenize, twoPipe) {
  tokenizerTest("ls -l || cat", {"ls", "-l", "||", "cat"});
}

TEST(Tokenize, oneAmpersantAndOnePipe) {
  tokenizerTest("ls -l & |", {"ls", "-l", "&", "|"});
}

TEST(Tokenize, oneArrowLeft) {
  tokenizerTest("ls -l < cat", {"ls", "-l", "<", "cat"});
}

TEST(Tokenize, twoArrowLeft) {
  tokenizerTest("ls -l << cat", {"ls", "-l", "<<", "cat"});
}

TEST(Tokenize, oneArrowRight) {
  tokenizerTest("ls -l > cat", {"ls", "-l", ">", "cat"});
}

TEST(Tokenize, twoArrowRight) {
  tokenizerTest("ls -l >> cat", {"ls", "-l", ">>", "cat"});
}

TEST(Tokenize, oneDollar) { //
  tokenizerTest("ls -l $", {"ls", "-l", "$"});
}

TEST(Tokenize, oneDollarWithWord) {
  tokenizerTest("ls -l $word", {"ls", "-l", "$word"});
}

TEST(Tokenize, oneDollarWithWordAndOneAmpersant) {
  tokenizerTest("ls -l $word &", {"ls", "-l", "$word", "&"});
}

TEST(Tokenize, oneArrowRightAndOneArrowLeft) {
  tokenizerTest("ls -l > cat < cat", {"ls", "-l", ">", "cat", "<", "cat"});
}

TEST(Tokenize, oneArrowRightAndOneArrowLeftAndOnePipe) {
  tokenizerTest("ls -l > cat < cat |",
                {"ls", "-l", ">", "cat", "<", "cat", "|"});
}

/***************************** Random ***************************************/

TEST(TokenizeRandom, manyQuotes) {
  tokenizerTest("'''''''''''''", {"'''''''''''''"});
}

TEST(TokenizeRandom, manyQuotesAndWord) {
  tokenizerTest("''''''''''''' word", {"'''''''''''''", "word"});
}

TEST(TokenizeRandom, manyQuotesAndWordAndQuotes) {
  tokenizerTest("''''''''''''' word '''''''''''''",
                {"'''''''''''''", "word", "'''''''''''''"});
}

TEST(TokenizeRandom, manyDQuotes) {
  tokenizerTest("\"\"\"\"\"\"\"\"\"\"\"", {"\"\"\"\"\"\"\"\"\"\"\""});
}

TEST(TokenizeRandom, manyDQuotesAndWord) {
  tokenizerTest("\"\"\"\"\"\"\"\"\"\"\" word",
                {"\"\"\"\"\"\"\"\"\"\"\"", "word"});
}

TEST(TokenizeRandom, manyDQuotesAndWordAndDQuotes) {
  tokenizerTest("\"\"\"\"\"\"\"\"\"\"\" word \"\"\"\"\"\"\"\"\"\"\"",
                {"\"\"\"\"\"\"\"\"\"\"\"", "word", "\"\"\"\"\"\"\"\"\"\"\""});
}

TEST(TokenizeRandom, manyDollars) {
  tokenizerTest("$$$$$$$$$$$$$$", {"$$$$$$$$$$$$$$"});
}

TEST(TokenizeRandom, manyDollarsAndWord) {
  tokenizerTest("$$$$$$$$$$$$$$ word", {"$$$$$$$$$$$$$$", "word"});
}

TEST(TokenizeRandom, manyBackslash) {
  tokenizerTest("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\",
                {"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"});
}

TEST(TokenizeRandom, manyBackslashInQuotes) {
  tokenizerTest("'\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\'",
                {"'\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\'"});
}

/***************************** TokenizeSpecial ********************************/

TEST(TokenizeSpecial, errorRedirection) {
  tokenizerTest("ls >>", {"ls", ">>"});
  // TODO si on lit la consigne, meme pas besoin de gerer ca
  // tokenizerTest("ls -l 2>", {"ls", "-l", "2>"});
  // tokenizerTest("ls &2>", {"ls", "&2>"});
  // tokenizerTest("ls &>", {"ls", "&>"});

  // 2>>
  // 2>&1
  // 2>&-
  // 2>&1
}

TEST(TokenizeSpecial, dollardAndQuestionMark) {
  tokenizerTest("echo $? $?", {"echo", "$?", "$?"});
}

TEST(TokenizeSpecial, dollarAlone) {
  tokenizerTest("echo $|cat", {"echo", "$", "|", "cat"});
}

TEST(TokenizeSpecial, dollarAlone2) {
  tokenizerTest("echo $\"|cat\"", {"echo", "$\"|cat\""});
}

TEST(TokenizeSpecial, assignation) {
  tokenizerTest("a=1", {"a=1"});
  tokenizerTest("a=1 b=2", {"a=1", "b=2"});
  tokenizerTest("a= 1", {"a=", "1"});
  tokenizerTest(" a = 1", {"a", "=", "1"});
}

/*
TEST(TokenizeSpecial, arithmeticExpansion) {
  // TODO ca doit faire ca ?? -> NON
  tokenizerTest("echo $( 2 )", {"echo", "$( 2 )"});
  tokenizerTest("echo $((( )))", {"echo", "$((( )))"}); // Devrait crash
  tokenizerTest("echo $((( 0 )))", {"echo", "$((( 0 )))"});
  tokenizerTest("echo $(( ))", {"echo", "$(( ))"}); // Devrait echo 0
}

TEST(TokenizeSpecial, math) {
  tokenizerTest("echo $((1+1))", {"echo", "$((1+1))"});
  tokenizerTest("2+2", {"2+2"});
  tokenizerTest("2 +2", {"2", "+2"});
}
*/
