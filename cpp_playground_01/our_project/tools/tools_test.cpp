#include <gtest/gtest.h>

namespace our_project {
namespace tools {
int get_meaning_of_life() { return 42; }
}  // namespace tools
}  // namespace our_project

TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
  // wrong test
  EXPECT_EQ(43, 42);
}
