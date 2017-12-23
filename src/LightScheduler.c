#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"

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
  Time time;
  TimeService_GetTime(&time);

  if(scheduledEvent.id == UNUSED)
    return;
  if(time.minuteOfDay != scheduledEvent.minuteOfDay)
    return;
  
  LightController_On(scheduledEvent.id);
}