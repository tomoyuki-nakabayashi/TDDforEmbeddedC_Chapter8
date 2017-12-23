#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"

enum
{
  UNUSED = -1,
  TURN_OFF,
  TURN_ON
};

typedef struct {
  int id;
  int minuteOfDay;
  int event;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvent;

void LightScheduler_Create(void)
{
  scheduledEvent.id = UNUSED;
}

void LightScheduler_Destory(void)
{

}

static void scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
  scheduledEvent.id = id;
  scheduledEvent.event = event;
  scheduledEvent.minuteOfDay = minuteOfDay;
}

void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
  scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
  scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

static void operateLight(ScheduledLightEvent *lightEvent)
{
  if(lightEvent->event == TURN_ON)
    LightController_On(lightEvent->id);
  else if(lightEvent->event == TURN_OFF)
    LightController_Off(lightEvent->id);
}

static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent)
{
  if(lightEvent->id == UNUSED)
    return;

  if(lightEvent->minuteOfDay != time->minuteOfDay)
    return;
  
  operateLight(lightEvent);
}

void LightScheduler_Wakeup(void)
{
  Time time;
  TimeService_GetTime(&time);

  if(scheduledEvent.id == UNUSED)
    return;
  if(time.minuteOfDay != scheduledEvent.minuteOfDay)
    return;
  
  if(scheduledEvent.event == TURN_ON)
    LightController_On(scheduledEvent.id);
  else if(scheduledEvent.event == TURN_OFF)
    LightController_Off(scheduledEvent.id);
}