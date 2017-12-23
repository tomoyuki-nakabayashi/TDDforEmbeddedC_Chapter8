#ifndef TEST_LIGHT_CONTROLLER_SPY_H_
#define TEST_LIGHT_CONTROLLER_SPY_H_

#include "LightController.h"

enum {
  LIGHT_ID_UNKNOWN = -1,
  LIGHT_STATE_UNKNOWN = -1,
  LIGHT_OFF = 0,
  LIGHT_ON = 1
};

int LightControllerSpy_GetLastId(void);
int LightControllerSpy_GetLastState(void);
int LightControllerSpy_GetLightState(int id);

#endif //TEST_LIGHT_CONTROLLER_SPY_H_