#include <iostream>
#include "gtest/gtest.h"
#include "Position.h"


TEST(PositionTest, setters_getters)
{
  Position pos;
  pos.set_x(2.0);
  ASSERT_EQ(pos.get_x(), 2.0);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
