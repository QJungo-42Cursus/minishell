#define TEST // Will hide the true main function

#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/***** OLD C TESTS (visual tests) *****

#define PADDING "----------------------------------------"

void title(char *str, char *line, int line_n) {
  ft_color(BLUE, BOLD);
  printf("%s %s (ligne %d)\n", PADDING, str, line_n);
  fflush(stdout);
  printf("%s\n", line);
  ft_color(RESET, RESET);
  fflush(stdout);
}

void foot(t_list *tokens) {
  ft_printf("result : ");
  fflush(stdout);
  ft_color(PURPLE, BOLD);
  fflush(stdout);
  log_tokens(tokens);
  printf("\n%s END\n\n", PADDING);
  fflush(stdout);
  ft_color(RESET, RESET);
  fflush(stdout);
}

void in(t_bool error, char *str, int line_n) {
  char *line = ft_strdup(str);
  if (line == NULL)
    return;
  if (!error) {
    title("Normal mode", line, line_n);
    foot(tokenizer(line));
    free(line); // TODO c'est mistique, si je le free, quand je lui reasigne
                // ft_strdup(str), il crash (pas sur que ce soit ca);
  } else {
    char *tmp = ft_strdup(line);
    if (fork() == 0) // Fork pour pouvoir crash !
    {
      // TODO pour l'instant, ca me fait un malloc error
      title("Error mode", tmp, line_n);
      foot(tokenizer(tmp));
      free(line);
      return;
    } else {
      wait(NULL);
      return;
    }
  }
}

* TEST TOKENIZER *
void test() {
  *
   * J'ai l'impression que ce test est casse
   * Les fonctions on l'air de fonctionner
   * J'hesite a faire un truc en rust ou python qui lit le stdout...
   *
  in(FALSE, "echo salut && echo bye\"", __LINE__);
  in(FALSE, "echo salut >", __LINE__);
  in(FALSE, "echo \"\"salut", __LINE__);
  in(FALSE, "echo", __LINE__);

  in(FALSE, "echo salut\" s\"",
     __LINE__); // DQUOTE after word, should concat auto
  in(FALSE, "echo ' salut ' ", __LINE__); // OK
  return;
  in(FALSE, "echo salut' s'  ",
     __LINE__); // QUOTE after word, should concat auto
  in(FALSE, "echo ' salut\\'  '' ", __LINE__); // QUOTE empty and nothiing after
  in(FALSE, "echo \" salut\\\" \" ", __LINE__); // OK
  in(FALSE, "echo salut > salut 2> >", __LINE__);
  in(FALSE, "echo salut>salut", __LINE__);
  in(FALSE, "echo salut <<&&>> echo bye", __LINE__);
  in(FALSE, "echo salut < > &> &2> 22 <<&&>> echo bye", __LINE__);
  in(FALSE, "echo \"salut < > &> &2> 22 <<&&>> echo bye", __LINE__);
  return;
  in(FALSE, "echo salut >> || << && ;", __LINE__);

  // in(TRUE, "echo \" salut\\\" \"               \"     ", __LINE__); // ERROR
  // DQUOTE not closed in(TRUE, "echo ' salut\\'                '     ",
  // __LINE__); // ERROR QUOTE not closed
}

*/
