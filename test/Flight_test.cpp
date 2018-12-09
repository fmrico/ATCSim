
#include <iostream>
#include "gtest/gtest.h"
#include "Flight.h"
#include "Position.h"


TEST(FlightTest, constructor)
{
Flight f1("IB001", Position(1,2,3), 1.0, 2.0, CRASH_SPEED_MAX);
Position pos = f1.getPosition();


ASSERT_EQ(f1.getId(), "IB001");
  ASSERT_EQ(pos.get_x(), 1.0);
ASSERT_EQ(pos.get_y(), 2.0);
ASSERT_EQ(pos.get_z(), 3.0);
  ASSERT_EQ(f1.getBearing(), 1.0);
  ASSERT_EQ(f1.getInclination(), 2.0);
ASSERT_EQ(f1.getSpeed(), CRASH_SPEED_MAX);
ASSERT_EQ(f1.getPoints(), INIT_FLIGHT_POINTS);
}


TEST(FlightTest, id)
{
  Flight f1("IB001", Position(0,0,0), 0.0, 0.0, 0.0);
  ASSERT_EQ(f1.getId(), "IB001");
}


TEST(FlightTest, empty_id)
{
  Flight f1("", Position(0,0,0), 0.0, 0.0, 0.0);
  ASSERT_EQ(f1.getId(), "");
}


TEST(FlightTest, set_get_speed_over_limit)
{
  Flight f1("", Position(0,0,0), 0.0, 0.0, 0.0);
f1.setSpeed(CRASH_SPEED_MAX + 100);
  ASSERT_EQ(f1.getSpeed(), CRASH_SPEED_MAX);
}


TEST(FlightTest, set_get_speed_under_limit)
{
  Flight f1("", Position(0,0,0), 0.0, 0.0, 0.0);
f1.setSpeed(CRASH_SPEED_MAX - 100);
  ASSERT_EQ(f1.getSpeed(), CRASH_SPEED_MAX - 100);
}


TEST(FlightTest, set_get_in_storm)
{
  Flight f1("f1", Position(0,0,0), 0.0, 0.0, 0.0);
Flight f2("f2", Position(0,0,0), 0.0, 0.0, 0.0);
f1.setInStorm(true);
f2.setInStorm(false);
  ASSERT_EQ(f1.getInStorm(), true);
ASSERT_EQ(f2.getInStorm(), false);
}


TEST(FlightTest, set_get_focused)
{
  Flight f1("f1", Position(0,0,0), 0.0, 0.0, 0.0);
Flight f2("f2", Position(0,0,0), 0.0, 0.0, 0.0);
f1.setFocused(true);
f2.setFocused(false);
  ASSERT_EQ(f1.getFocused(), true);
ASSERT_EQ(f2.getFocused(), false);
}


TEST(FlightTest, bearing)
{
  Flight f1("f1", Position(0,0,0), 14.0, 0.0, 0.0);
  ASSERT_EQ(f1.getBearing(), 14.0);
}

TEST(FlightTest, inclination)
{
  Flight f1("f1", Position(0,0,0), 0.0, 14.0, 0.0);
  ASSERT_EQ(f1.getInclination(), 14.0);
}


TEST(FlightTest, points)
{
  Flight f1("f1", Position(0,0,0), 0.0, 0.0, 0.0);
  ASSERT_EQ(f1.getPoints(), INIT_FLIGHT_POINTS);
}


TEST(FlightTest, position)
{
  Flight f1("f1", Position(1,2,3), 0.0, 0.0, 0.0);
Position pos = f1.getPosition();
  ASSERT_EQ(pos.get_x(), 1.0);
ASSERT_EQ(pos.get_y(), 2.0);
ASSERT_EQ(pos.get_z(), 3.0);
}

/*
TEST(FlightTest, update)
{
  Flight f1("f1", Position(0,0,0), 0.0, 0.0, 0.0);
f1.update(0.0);
printf("%f-----\n", f1.getPoints());
ASSERT_EQ(f1.getPoints(), INIT_FLIGHT_POINTS-2);
}
*/



int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

