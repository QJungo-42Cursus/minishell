#include "gtest/gtest.h"
// #include <array>
// #include <iostream>

extern "C" {
#include "../builtins/builtins.h"
#include "../libft/libft.h"
#include "../tokenizer/tokenizer.h"
}

void testEcho(std::vector<std::string> args, std::string expected) {
  char **argv = (char **)malloc(sizeof(char *) * (args.size() + 1));
  for (size_t i = 0; i < args.size(); i++) {
    argv[i] = (char *)args[i].c_str();
  }
  argv[args.size()] = NULL;
  testing::internal::CaptureStdout();
  echo((char **)argv);
  std::string output = testing::internal::GetCapturedStdout();
  EXPECT_EQ(output, expected);
}

TEST(Echo, helloWorld) {
  testEcho({"echo", "hello", "world"}, "hello world\n");
}

TEST(Echo, withN) {
  testEcho({"echo", "-n", "world"}, "world");
}
