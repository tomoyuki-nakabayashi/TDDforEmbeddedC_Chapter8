#include "FakeTimeService.h"

static int minuteOfDay;
static int dayOfWeek;

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

void FakeTimeService_SetMinute(int minute)
{
  minuteOfDay = minute;
}

void FakeTimeService_SetDay(int day)
{
  dayOfWeek = day;
}
