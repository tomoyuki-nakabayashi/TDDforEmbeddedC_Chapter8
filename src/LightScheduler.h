#ifndef SRC_LIGHT_SCHEDULER_H_
#define SRC_LIGHT_SCHEDULER_H_

typedef enum  {
    NONE=-1, EVERYDAY=10, WEEKDAY, WEEKEND,
    SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
} Day;

enum {
    LS_ID_OUT_OF_BOUNDS = -2,
    LS_TOO_MANY_EVENTS = -1,
    LS_OK = 0
};

void LightScheduler_Create(void);
void LightScheduler_Destory(void);
int LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
int LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleRemove(int id, Day day, int minuteOfDay);
void LightScheduler_Wakeup(void);

#endif //SRC_LIGHT_SCHEDULER_H_