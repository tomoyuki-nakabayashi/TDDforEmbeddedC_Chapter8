#ifndef SRC_TIME_SERVICE_H_
#define SRC_TIME_SERVICE_H_

typedef struct TimeStruct {
  int minuteOfDay;
  int dayOfWeek;
} Time;

void TimeService_Create(void);
void TimeService_Destory(void);
void TimeService_GetTime(Time *time);

#endif SRC_TIME_SERVICE_H_
