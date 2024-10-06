#include <gtest/gtest.h>

#include "networking_tools.hpp"

using namespace our_project::networking_tools;

TEST(push_pop_queue_with_async_test, BasicAssertions) {
  EXPECT_EQ(24, push_pop_queue_with_async(4));
}
