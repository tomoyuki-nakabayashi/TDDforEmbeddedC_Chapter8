#include "gtest/gtest.h"
extern "C" {
  #include "LightScheduler.h"
  #include "LightControllerSpy.h"
  #include "FakeTimeService.h"
}

namespace light_scheduler_test{

  class LightSchedulerTest : public ::testing::Test
  {
    virtual void SetUp()
    {
      LightController_Create();
      LightScheduler_Create();
    }
    virtual void TearDown()
    {
      LightController_Destory();
      LightScheduler_Destory();
    }
  };

  TEST_F(LightSchedulerTest, NoChangeToLightsDuringInitialization)
  {
    EXPECT_EQ(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    EXPECT_EQ(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
  }

  TEST_F(LightSchedulerTest, NoScheduleNothingHppens)
  {
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_Wakeup();
    EXPECT_EQ(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    EXPECT_EQ(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
  }

  TEST_F(LightSchedulerTest, ScheduleOnEverydayNotTimeYet)
  {
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);
    LightScheduler_Wakeup();

    EXPECT_EQ(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    EXPECT_EQ(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
  }

  TEST_F(LightSchedulerTest, ScheduleOnEverydayItsTime)
  {
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);
    LightScheduler_Wakeup();

    EXPECT_EQ(3, LightControllerSpy_GetLastId());
    EXPECT_EQ(LIGHT_ON, LightControllerSpy_GetLastState());
  }
} // namespace
