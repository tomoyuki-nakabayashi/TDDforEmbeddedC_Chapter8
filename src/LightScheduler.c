#include "LightScheduler.h"

typedef struct {
  int id;
  int minuteOfDay;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create(void)
{
  scheduledEvent.id = UNUSED;
}

void LightScheduler_Destory(void)
{

}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
  scheduledEvent.id = id;
  scheduledEvent.minuteOfDay = minuteOfDay;
}

void LightScheduler_Wakeup(void)
{

}