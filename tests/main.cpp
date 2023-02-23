#include "all.h"
#include "gtest/gtest.h"
#include <iostream>

char **g_envp;
int main(int argc, char **argv, char **envp) {
  g_envp = cpy_envp(envp);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
