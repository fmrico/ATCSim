#include <iostream>
#include "gtest/gtest.h"
#include "Position.h"

using namespace atcsim;

TEST(PositionTest, empty_constructor)
{
	Position pos;
	ASSERT_EQ(pos.get_x(), 0.0);
	ASSERT_EQ(pos.get_y(), 0.0);
	ASSERT_EQ(pos.get_z(), MAINTAIN_ALT);
}


TEST(PositionTest, constructor)
{
	Position pos(1,2,3);
	ASSERT_EQ(pos.get_x(), 1.0);
	ASSERT_EQ(pos.get_y(), 2.0);
	ASSERT_EQ(pos.get_z(), 3.0);
}


TEST(PositionTest, setters_getters)
{
	Position pos;
	pos.set_x(1.0);
	pos.set_y(2.0);
	pos.set_z(3.0);
	ASSERT_EQ(pos.get_x(), 1.0);
	ASSERT_EQ(pos.get_y(), 2.0);
	ASSERT_EQ(pos.get_z(), 3.0);
}

TEST(PositionTest, short_distance)
{
	Position pos1(1, 0, 0);
	Position pos2(2, 0, 0);
	ASSERT_EQ(pos1.distance(pos2), 1.0);
}


TEST(PositionTest, long_distance)
{
	Position pos1(1, 0, 0);
	Position pos2(200, 1500, 300);
	ASSERT_FLOAT_EQ(pos1.distance(pos2), 1542.5956);
}


TEST(PositionTest, zero_distance)
{
	Position pos1(2, 0, 0);
	Position pos2(2, 0, 0);
	ASSERT_EQ(pos1.distance(pos2), 0.0);
}


TEST(PositionTest, positive_angles)
{
	Position pos1(1, 0, 1);
	Position pos2(2, 0, 5);
	float bearing, inclination;
	pos1.angles(pos2, bearing, inclination);
	ASSERT_FLOAT_EQ(bearing, 3.1415927);
	ASSERT_FLOAT_EQ(inclination, 1.325818);
}


TEST(PositionTest, negative_angles)
{
	Position pos1(10, -10, 10);
	Position pos2(0, 0, 0);
	float bearing, inclination;
	pos1.angles(pos2, bearing, inclination);
	ASSERT_FLOAT_EQ(bearing, -0.785398);
	ASSERT_FLOAT_EQ(inclination, -0.61547971);

}

TEST(PositionTest, zero_angles)
{
	Position pos1(2, 0, 0);
	Position pos2(2, 0, 0);
	float bearing, inclination;
	pos1.angles(pos2, bearing, inclination);
	ASSERT_EQ(bearing, 0.0);
	ASSERT_EQ(inclination, 0.0);
}


int main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}
