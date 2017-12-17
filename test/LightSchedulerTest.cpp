#include "gtest/gtest.h"
extern "C" {
  #include "LightScheduler.h"
}

namespace light_scheduler_test{

class LightSchedulerTest : public ::testing::Test
{
  virtual void SetUp()
  {
  }
  virtual void TearDown()
  {
  }
};

TEST_F(LightSchedulerTest, ScheduleOnEverydayNotTimeYet)
{
  virtualLeds = 0xffff;

  LedDriverTurnOn(8);
  EXPECT_EQ(0x80, virtualLeds);
}


} // namespace
