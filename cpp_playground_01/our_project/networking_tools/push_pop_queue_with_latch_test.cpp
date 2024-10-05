#include <gtest/gtest.h>

#include "networking_tools.hpp"

using namespace our_project::networking_tools;

TEST(push_pop_queue_with_latch_test, BasicAssertions) {
  EXPECT_EQ(30, push_pop_queue_with_latch(5));
}
