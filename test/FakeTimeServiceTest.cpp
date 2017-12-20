#include "gtest/gtest.h"
extern "C" {
  #include "LightScheduler.h"
  #include "FakeTimeService.h"
}

namespace fake_time_service_test{
  class FakeTimeServiceTest : public ::testing::Test
  {
    virtual void SetUp()
    {
      TimeService_Create();
    }

    virtual void TearDown()
    {
      TimeService_Destory();
    }
  };

  TEST_F(FakeTimeServiceTest, Create)
  {
    Time time;
    TimeService_GetTime(&time);
    EXPECT_EQ(TIME_UNKNOWN, time.minuteOfDay);
    EXPECT_EQ(TIME_UNKNOWN, time.dayOfWeek);
  }

  TEST_F(FakeTimeServiceTest, Set)
  {
    Time time;
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SATURDAY);
    TimeService_GetTime(&time);
    EXPECT_EQ(42, time.minuteOfDay);
    EXPECT_EQ(SATURDAY, time.dayOfWeek);
  }
} // namespace fake_time_service_test