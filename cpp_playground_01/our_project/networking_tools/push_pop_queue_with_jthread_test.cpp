#include <gtest/gtest.h>

#include "networking_tools.hpp"

using namespace our_project::networking_tools;

TEST(push_pop_queue_with_jthread_test, BasicAssertions) {
  EXPECT_EQ(48, push_pop_queue_with_jthread(8));
}
