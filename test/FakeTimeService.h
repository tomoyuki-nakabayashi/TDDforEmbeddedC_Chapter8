#ifndef TEST_FAKE_TIME_SERVICE_H_
#define TEST_FAKE_TIME_SERVICE_H_

#include "TimeService.h"

enum {
  TIME_UNKNOWN = -1,
};

void FakeTimeService_SetMinute(int minute);
void FakeTimeService_SetDay(int day);
WakeupCallback FakeTimeService_GetAlarmCallcack(void);
int FakeTimeService_GetAlarmPeriod(void);

#endif //TEST_FAKE_TIME_SERVICE_H_
