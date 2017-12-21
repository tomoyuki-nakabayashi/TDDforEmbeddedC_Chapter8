#ifndef SRC_LIGHT_SCHEDULER_H_
#define SRC_LIGHT_SCHEDULER_H_

typedef enum  {
    NONE=-1, EVERYDAY=10, WEEKDAY, WEEKEND,
    SUNDAY=1, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
} Day;

void LightScheduler_Create(void);
void LightScheduler_Destory(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
void LightScheduler_Wakeup(void);

#endif //SRC_LIGHT_SCHEDULER_H_