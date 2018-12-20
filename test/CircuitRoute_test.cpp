#include <iostream>
#include "gtest/gtest.h"
#include "CircuitRoute.h"


TEST(CircuitRouteTest, loadNavPoints)
{
    int error_code = atcsim::loadNavPoints();

    if(error_code == EXIT_SUCCESS)
        ASSERT_GE(atcsim::getRoutePoints().size(), 0);
    else
        ASSERT_EQ(atcsim::getRoutePoints().size(), 0);
}

TEST(CircuitRouteTest, loadNavCircuits)
{
    int error_code = atcsim::loadNavCircuits();

    if(error_code == EXIT_SUCCESS)
        ASSERT_GE(atcsim::getRouteCircuits().size(), 0);
    else
        ASSERT_EQ(atcsim::getRouteCircuits().size(), 0);
}


int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
