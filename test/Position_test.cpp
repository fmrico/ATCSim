#include <iostream>
#include "gtest/gtest.h"
#include "Position.h"


TEST(PositionTest, setters_getters)
{
  atcsim::Position pos;
  pos.set_x(1.0);
  pos.set_y(2.0);
  pos.set_z(3.0);
  ASSERT_EQ(pos.get_x(), 1.0);
  ASSERT_EQ(pos.get_y(), 2.0);
  ASSERT_EQ(pos.get_z(), 3.0);

  pos.set_name("WPT01");
  ASSERT_STREQ(pos.get_name().c_str(), "WPT01");
  pos.set_name("WPT");
  ASSERT_STREQ(pos.get_name().c_str(), "WPT00");
  pos.set_name("WAYPOINT");
  ASSERT_STREQ(pos.get_name().c_str(), "WAYPO");
}

TEST(PositionTest, distance)
{
  atcsim::Position pos1(1, 0, 0);
  atcsim::Position pos2(2, 0, 0);
  ASSERT_EQ(pos1.distance(pos2), 1.0);
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
