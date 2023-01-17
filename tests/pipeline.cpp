#include "gtest/gtest.h"
#include <array>
#include <iostream>

extern "C" {
#include "../libft/libft.h"
void pipeline();
}

TEST(Pipeline, test1) {
	pipeline();
}
