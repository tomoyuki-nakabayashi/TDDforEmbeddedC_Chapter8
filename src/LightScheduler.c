#include <stdbool.h>
#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"

enum
{
  UNUSED = -1,
  TURN_OFF,
  TURN_ON,
  MAX_EVENTS = 128
};

typedef struct {
  int id;
  int minuteOfDay;
  int event;
  Day day;
} ScheduledLightEvent;

static ScheduledLightEvent scheduledEvents[MAX_EVENTS];

static int scheduleEvent(int id, Day day, int minuteOfDay, int event)
{
  if(id < 0 || id >= MAX_LIGHTS)
    return LS_ID_OUT_OF_BOUNDS;

  for(int i=0; i<MAX_EVENTS; i++)
  {
    if(scheduledEvents[i].id == UNUSED)
    {
      scheduledEvents[i].day = day;
      scheduledEvents[i].minuteOfDay = minuteOfDay;
      scheduledEvents[i].event = event;
      scheduledEvents[i].id = id;
      return LS_OK;
    }
  }
  return LS_TOO_MANY_EVENTS;
}

int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay)
{
  return scheduleEvent(id, day, minuteOfDay, TURN_ON);
}

int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay)
{
  return scheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay)
{
  for(int i=0; i<MAX_EVENTS; i++)
  {
    if((id == scheduledEvents[i].id) 
    && (day = scheduledEvents[i].day) 
    && (minuteOfDay == scheduledEvents[i].minuteOfDay))
    {
      scheduledEvents[i].id = UNUSED;
    }
  }
}

static void operateLight(ScheduledLightEvent *lightEvent)
{
  if(lightEvent->event == TURN_ON)
    LightController_On(lightEvent->id);
  else if(lightEvent->event == TURN_OFF)
    LightController_Off(lightEvent->id);
}

static bool DoesLightRespondToday(const int today, const int reactionDay)
{
  if(reactionDay == EVERYDAY)
    return true;
  
  if(reactionDay == today)
    return true;

  if((reactionDay == WEEKEND) && (today == SATURDAY || today == SUNDAY))
    return true;
  
  if((reactionDay == WEEKDAY) && (today >= MONDAY && today <= FRIDAY))
    return true;

  return false;
}

static void processEventDueNow(Time *time, ScheduledLightEvent *lightEvent)
{
  int reactionDay = lightEvent->day;
  Day today = time->dayOfWeek;
  if(lightEvent->id == UNUSED)
    return;
  if(DoesLightRespondToday(today, reactionDay) == false)
    return;
  if(lightEvent->minuteOfDay != time->minuteOfDay)
    return;
  
  operateLight(lightEvent);
}

void LightScheduler_Wakeup(void)
{
  Time time;
  TimeService_GetTime(&time);

  for(int i=0; i<MAX_EVENTS; i++)
  {
    processEventDueNow(&time, &scheduledEvents[i]);
  }
}

void LightScheduler_Create(void)
{
  for(int i=0; i<MAX_EVENTS; i++)
  {
    scheduledEvents[i].id = UNUSED;
  }
  TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}

void LightScheduler_Destory(void)
{
  TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_Wakeup);
}