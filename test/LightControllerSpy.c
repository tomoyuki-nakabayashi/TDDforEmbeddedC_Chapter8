#include "LightControllerSpy.h"
#include <string.h>

static int lastId;
static int lastState;
static int lights[MAX_LIGHTS];

/*** Pseudo implementation of collaborator's interface ***/
void LightController_Create(void)
{
  lastId = LIGHT_ID_UNKNOWN;
  lastState = LIGHT_STATE_UNKNOWN;
  memset(lights, LIGHT_STATE_UNKNOWN, sizeof(lights));
}

void LightController_Destory(void)
{
  lastId = LIGHT_ID_UNKNOWN;
  lastState = LIGHT_STATE_UNKNOWN;
}

void LightController_On(int id)
{
  lastId = id;
  lastState = LIGHT_ON;
  lights[id] = LIGHT_ON;
}

void LightController_Off(int id)
{
  lastId = id;
  lastState = LIGHT_OFF;
  lights[id] = LIGHT_OFF;
}

/*** Spy functions ***/
int LightControllerSpy_GetLastId(void)
{
  return lastId;
}

int LightControllerSpy_GetLastState(void)
{
  return lastState;
}

int LightControllerSpy_GetLightState(int id)
{
  return lights[id];
}