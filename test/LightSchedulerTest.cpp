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

  TEST_F(LightSchedulerTest, RejectsTooManyEvents)
  {
    int i;
    for(i=0; i<128; i++)
      EXPECT_EQ(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
    
    EXPECT_EQ(LS_TOO_MANY_EVENTS, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
  }

  TEST_F(LightSchedulerTest, RemoveRecyclesScheduleSlot)
  {
    for(int i; i<128; i++)
      EXPECT_EQ(LS_OK, LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
    
    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    EXPECT_EQ(LS_OK, LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
  }

  TEST_F(LightSchedulerTest, RemoveMultipleScheduledEvent)
  {
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);
    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    setTimeTo(MONDAY, 600);

    LightScheduler_Wakeup();

    checkLightState(6, LIGHT_STATE_UNKNOWN);
    checkLightState(7, LIGHT_ON);
  }

  TEST_F(LightSchedulerTest, AcceptsValidLightIds)
  {
    EXPECT_EQ(LS_OK, LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
    EXPECT_EQ(LS_OK, LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
    EXPECT_EQ(LS_OK, LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
  }

  TEST_F(LightSchedulerTest, RejectsInvalidLightIds)
  {
    EXPECT_EQ(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
    EXPECT_EQ(LS_ID_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
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
