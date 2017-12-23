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
  protected:
    void setTimeTo(int day, int minuteOfDay)
    {
      FakeTimeService_SetDay(day);
      FakeTimeService_SetMinute(minuteOfDay);
    }

    void checkLightState(int id, int level)
    {
      EXPECT_EQ(id, LightControllerSpy_GetLastId());
      EXPECT_EQ(level, LightControllerSpy_GetLastState());
    }
  };

  TEST_F(LightSchedulerTest, NoChangeToLightsDuringInitialization)
  {
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
  }

  TEST_F(LightSchedulerTest, NoScheduleNothingHppens)
  {
    setTimeTo(MONDAY, 100);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
  }

  TEST_F(LightSchedulerTest, ScheduleOnEverydayNotTimeYet)
  {
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1199);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
  }

  TEST_F(LightSchedulerTest, ScheduleOnEverydayItsTime)
  {
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);
  }

  TEST_F(LightSchedulerTest, ScheduleOffEverydayItsTime)
  {
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_OFF);
  }

  TEST_F(LightSchedulerTest, ScheduleTeusdayButItsMonday)
  {
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
  }

  TEST_F(LightSchedulerTest, ScheduleTeusdayAndItsTuesday)
  {
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    setTimeTo(TUESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
  }

  TEST_F(LightSchedulerTest, ScheduleWeekEndItsFriday)
  {
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
  }

  TEST_F(LightSchedulerTest, ScheduleWeekEndItsSaturday)
  {
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SATURDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
  }

  TEST_F(LightSchedulerTest, ScheduleWeekEndItsSunday)
  {
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
  }

  TEST_F(LightSchedulerTest, ScheduleWeekEndItsMonday)
  {
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
  }
} // namespace
