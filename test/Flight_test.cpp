#include <iostream>
#include "gtest/gtest.h"
#include "Flight.h"
#include "Position.h"


TEST(FlightTest, id)
{
  Flight f1("IB001", Position(0,0,0), 0.0, 0.0, 0.0);
  ASSERT_EQ(f1.getId(), "IB001");
}

int main(int argc, char* argv[])
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
