#include "gtest/gtest.h"
#include <array>
#include <iostream>

extern "C" {
#include "../libft/libft.h"
#include "../tokenizer/tokenizer.h"
}

void tokenizerTest(const char *sentence, std::vector<std::string> expected) {
  // int	tokenizer(const char *cmd, t_list **tokens, t_bool is_expand_mode,
  // t_minishell *minishell)

  t_list *tokens;
  tokenizer(sentence, &tokens, FALSE,
            (t_minishell *)malloc(sizeof(t_minishell)));
  t_list *current = tokens;
  for (size_t i = 0; current != nullptr && i < expected.size(); i++) {
    EXPECT_EQ(std::string((char *)current->content), expected[i]);
    // std::cout << "expected: " << expected[i] << std::endl;
    // std::cout << "actual: " << (char *)current->content << std::endl;
    // std::cout << "----------------" << std::endl;
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

TEST(TokenizeSpecial, script) {
  tokenizerTest("./script.sh", {"./script.sh"});
  tokenizerTest("./script.sh arg1 arg2", {"./script.sh", "arg1", "arg2"});
  tokenizerTest("../../script.sh arg1 arg2",
                {"../../script.sh", "arg1", "arg2"});
}

/***************************** TokenizeMean ***********************************/

TEST(TokenizeMean, nothing) { tokenizerTest("", {}); }

TEST(TokenizeMean, spaceAlone) { tokenizerTest(" ", {}); }

TEST(TokenizeMean, manySpacesAlone) { tokenizerTest("     ", {}); }

TEST(TokenizeMean, manySpacesAndWord) { tokenizerTest("     word", {"word"}); }

TEST(TokenizeMean, emptyQuoted) {
  tokenizerTest("\"  \"     word", {"\"  \"", "word"});
}

TEST(TokenizeMean, doubleBitch) {
  tokenizerTest("\"", {"\""});
  tokenizerTest("\"\"", {"\"\""});
}

/***************************** TokenizeParenthese *****************************/
TEST(TokenizeParenthese, simple) {
  tokenizerTest("(ls -l)", {"(", "ls", "-l", ")"});
}

TEST(TokenizeParenthese, simpleWithPipe) {
  tokenizerTest("(ls -l) | (ls -l)",
                {"(", "ls", "-l", ")", "|", "(", "ls", "-l", ")"});
}

TEST(TokenizeParenthese, simpleWithPipeAndWord) {
  tokenizerTest("(ls -l) | (ls -l) word",
                {"(", "ls", "-l", ")", "|", "(", "ls", "-l", ")", "word"});
}
