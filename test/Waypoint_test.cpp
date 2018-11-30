#include <iostream>
#include "gtest/gtest.h"
#include "AirControllerUtils.h"

std::string emptyStr = "";
std::string name1 = "WPT01";
std::string name2 = "WPT02";
float lat1, lon1 = 1000.0f;
float lat2, lon2 = -2000.0f;

TEST(WaypointTest, setters_getters)
{
    Waypoint *wpt0 = new Waypoint();
    Waypoint *wpt1 = new Waypoint();
    Waypoint *wpt2 = new Waypoint();

    wpt1->setName(name1);
    wpt1->setLat(lat1);
    wpt1->setLon(lon1);

    wpt2->setName(name2);
    wpt2->setLat(lat2);
    wpt2->setLon(lon2);

    ASSERT_STREQ( wpt0->getName().c_str(), emptyStr.c_str() );
    ASSERT_STREQ( wpt1->getName().c_str(), name1.c_str() );
    ASSERT_STREQ( wpt2->getName().c_str(), name2.c_str() );

    ASSERT_EQ( wpt0->getLat(), 0);
    ASSERT_EQ( wpt1->getLat(), lat1);
    ASSERT_EQ( wpt2->getLat(), lat2);

    ASSERT_EQ( wpt0->getLon(), 0);
    ASSERT_EQ( wpt1->getLon(), lon1);
    ASSERT_EQ( wpt2->getLon(), lon2);
}



int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
