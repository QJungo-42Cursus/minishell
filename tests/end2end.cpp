#include "gtest/gtest.h"

extern "C" {
#include "../libft/libft.h"
#include "../minishell.h"
int main_loop(t_minishell *minishell);
int	init_minishell(t_minishell *minishell, char **envp);
}

TEST(EndToEnd, EndToEnd) {
  t_minishell minishell;
  char **envp = getenv();
  if (init_minishell(&minishell, getenv()) == ERROR)
    return (EXIT_FAILURE);
  main_loop(&minishell);
  EXPECT_EQ(1, 1);
}
