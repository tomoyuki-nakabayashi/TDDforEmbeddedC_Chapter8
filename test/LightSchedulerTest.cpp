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
      if(id == LIGHT_ID_UNKNOWN)
      {
        EXPECT_EQ(id, LightControllerSpy_GetLastId());
        EXPECT_EQ(level, LightControllerSpy_GetLastState());
      }
      else
      {
        EXPECT_EQ(level, LightControllerSpy_GetLightState(id));
      }
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

  TEST_F(LightSchedulerTest, ScheduleWeeDayItsMonday)
  {
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(MONDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
  }

  TEST_F(LightSchedulerTest, ScheduleWeeDayItsFriday)
  {
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(FRIDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
  }

  TEST_F(LightSchedulerTest, ScheduleWeeDayItsWednesday)
  {
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(WEDNESDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(3, LIGHT_ON);
  }

  TEST_F(LightSchedulerTest, ScheduleWeeDayButItsSunday)
  {
    LightScheduler_ScheduleTurnOn(3, WEEKDAY, 1200);
    setTimeTo(SUNDAY, 1200);
    LightScheduler_Wakeup();
    checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
  }

  TEST_F(LightSchedulerTest, ScheduleTwoEventsAtTheSameTime)
  {
    LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);

    setTimeTo(SUNDAY, 1200);

    LightScheduler_Wakeup();

    checkLightState(3, LIGHT_ON);
    checkLightState(12, LIGHT_ON);
  }

  class LightSchedulerInitAndCleanup : public ::testing::Test
  {
  };

  TEST_F(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
  {
    LightScheduler_Create();
    EXPECT_EQ((void*)LightScheduler_Wakeup,
              (void*)FakeTimeService_GetAlarmCallcack());

    EXPECT_EQ(60, FakeTimeService_GetAlarmPeriod());
    LightScheduler_Destory();
  }

  TEST_F(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
  {
    LightScheduler_Create();
    LightScheduler_Destory();
    EXPECT_EQ(NULL, (void*)FakeTimeService_GetAlarmCallcack());
  }
} // namespace
