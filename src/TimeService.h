#ifndef SRC_TIME_SERVICE_H_
#define SRC_TIME_SERVICE_H_

typedef struct TimeStruct {
  int minuteOfDay;
  int dayOfWeek;
} Time;

typedef void (*WakeupCallback)(void);

void TimeService_Create(void);
void TimeService_Destory(void);
void TimeService_GetTime(Time *time);
void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback cb);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback cb);

#endif //SRC_TIME_SERVICE_H_
