extern "C" {
#include "../tokenizer/get_next_token_functions.c"
#include "../tokenizer/get_token_normal.c"
#include "../tokenizer/get_token_quote.c"
#include "../tokenizer/set_next_token_position.c"
#include "../tokenizer/tokenizer.c"

#include "../executor/pipeline.c"
}

#include "gtest/gtest.h"
#include <iostream>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
