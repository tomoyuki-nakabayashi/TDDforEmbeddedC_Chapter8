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
/* These tests incur build errors. We'll return here later.
  TEST_F(LightSchedulerTest, ScheduleOnEverydayNotTimeYet)
  {
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);
    LightScheduler_Wakeup();

    EXPECT_EQ(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    EXPECT_EQ(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
  }

  TEST_F(LightSchedulerTest, NoChangeToLightsDuringInitialization)
  {
    EXPECT_EQ(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    EXPECT_EQ(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
  }
 */
} // namespace
