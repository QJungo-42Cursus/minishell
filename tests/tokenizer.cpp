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

TEST(Tokenize, whiteSpaceBetweenWordsAndEndAndStart) {
  tokenizerTest("   ls   -l   ", {"ls", "-l"});
}

TEST(Tokenize, whiteSpaceBetweenWords) { //
  tokenizerTest("ls -l", {"ls", "-l"});
}

TEST(Tokenize, singleWord) { //
  tokenizerTest("word", {"word"});
}

TEST(Tokenize, oneAmpersant) { //
  tokenizerTest("ls -l &", {"ls", "-l", "&"});
}

TEST(Tokenize, twoAmpersant) {
  tokenizerTest("ls -l && cat", {"ls", "-l", "&&", "cat"});
}

TEST(Tokenize, onePipe) { tokenizerTest("ls -l |", {"ls", "-l", "|"}); }

TEST(Tokenize, twoPipe) {
  tokenizerTest("ls -l || cat", {"ls", "-l", "||", "cat"});
}

TEST(Tokenize, oneAmpersantAndOnePipe) {
  // TODO ?
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

TEST(Tokenize, oneDollar) { tokenizerTest("ls -l $", {"ls", "-l", "$"}); }

TEST(Tokenize, oneDollarWithWord) {
  tokenizerTest("ls -l $word", {"ls", "-l", "$word"});
}

TEST(Tokenize, oneDollarWithWordAndOneAmpersant) {
  tokenizerTest("ls -l $word &", {"ls", "-l", "$word", "&"});
}

// TODO bug avec le test ?
TEST(Tokenize, oneArrowRightAndOneArrowLeft) {
  tokenizerTest("ls -l > cat < cat", {"ls", "-l", ">", "cat", "<", "cat"});
}

TEST(Tokenize, oneArrowRightAndOneArrowLeftAndOnePipe) {
  tokenizerTest("ls -l > cat < cat |",
                {"ls", "-l", ">", "cat", "<", "cat", "|"});
}

// TODO add :
// 2>
// echo "$value"xxx
// echo "name"xxx"dum
// echo salut"salo"
// $((3+2)) (arithmetique substitution)
// copilot propose :
// 2>>
// 2>&1
// 2>&-
// 2>&1
