#include <iostream>
#include "gtest/gtest.h"
#include "AirControllerUtils.h"

std::string name1 = "WPT01";
std::string name2 = "WPT02";
float lat1, lon1 = 1000.0f;
float lat2, lon2 = -2000.0f;

TEST(AirControllerUtilsTest, createWaypoints)
{
    Waypoint *wpt1 = new Waypoint(name1, lat1, lon1);
    Waypoint *wpt2 = new Waypoint(name2, lat2, lon2);

    atc_utils::waypoints.push_back(wpt1);
    atc_utils::waypoints.push_back(wpt2);

    ASSERT_EQ(atc_utils::waypoints.size(), 2);
}

TEST(AirControllerUtilsTest, getWaypoints)
{
    std::list<Waypoint*> waypoints = atc_utils::getWaypoints();
    std::list<Waypoint*>::iterator it_wpt;

    ASSERT_EQ(waypoints.size(), 2);

    int count = 1;
    for(it_wpt = waypoints.begin(); it_wpt!=waypoints.end(); ++it_wpt){
        if(count == 1){
            ASSERT_STREQ( (*it_wpt)->getName().c_str(), name1.c_str());
        }else if(count == 2){
            ASSERT_STREQ( (*it_wpt)->getName().c_str(), name2.c_str());
        }

        count++;
	}
}

TEST(AirControllerUtilsTest, setWaypoints)
{
    atc_utils::setWaypoints();

    std::list<Waypoint*> waypoints = atc_utils::getWaypoints();
    std::list<Waypoint*>::iterator it_wpt;

    // Save it into a map in order to retrieve it by ID
    for(it_wpt = waypoints.begin(); it_wpt!=waypoints.end(); ++it_wpt){
        atc_utils::wpt_map.insert( std::pair<std::string, Waypoint>( (*it_wpt)->getName(), *(*it_wpt) ) );
    }

    ASSERT_EQ(atc_utils::wpt_map.size(), atc_utils::getWaypoints().size());
}

TEST(AirControllerUtilsTest, getWaypoint)
{

    ASSERT_STREQ( atc_utils::getWaypoint(name1).getName().c_str(), name1.c_str());
    ASSERT_STREQ( atc_utils::getWaypoint(name2).getName().c_str(), name2.c_str());
    ASSERT_STRNE( atc_utils::getWaypoint("XX").getName().c_str(), "XX");

    ASSERT_EQ( atc_utils::getWaypoint(name1).getLat(), lat1 );
    ASSERT_EQ( atc_utils::getWaypoint(name2).getLat(), lat2 );
    ASSERT_EQ( atc_utils::getWaypoint("XX").getLat(), 0 );

    ASSERT_EQ( atc_utils::getWaypoint(name1).getLon(), lon1 );
    ASSERT_EQ( atc_utils::getWaypoint(name2).getLon(), lon2 );
    ASSERT_EQ( atc_utils::getWaypoint("XX").getLon(), 0 );
}


int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
