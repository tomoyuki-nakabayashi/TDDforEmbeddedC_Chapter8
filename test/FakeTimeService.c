#include <stddef.h>
#include "FakeTimeService.h"

static int minuteOfDay;
static int dayOfWeek;
static WakeupCallback callback;
static int period;

void TimeService_Create(void)
{
  minuteOfDay = TIME_UNKNOWN;
  dayOfWeek = TIME_UNKNOWN;
}

void TimeService_Destory(void)
{
  minuteOfDay = TIME_UNKNOWN;
  dayOfWeek = TIME_UNKNOWN;
}

void TimeService_GetTime(Time *time)
{
  time->minuteOfDay = minuteOfDay;
  time->dayOfWeek = dayOfWeek;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb)
{
  callback = cb;
  period = seconds;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb)
{
  if(cb == callback && period == seconds)
  {
    callback = NULL;
    period = 0;
  }
}

void FakeTimeService_SetMinute(int minute)
{
  minuteOfDay = minute;
}

void FakeTimeService_SetDay(int day)
{
  dayOfWeek = day;
}

WakeupCallback FakeTimeService_GetAlarmCallcack(void)
{
  return callback;
}

int FakeTimeService_GetAlarmPeriod(void)
{
  return period;
}
