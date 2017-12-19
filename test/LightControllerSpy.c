#include "LightControllerSpy.h"

static int lastId;
static int lastState;

/*** Pseudo implementation of collaborator's interface ***/
void LightController_Create(void)
{
  lastId = LIGHT_ID_UNKNOWN;
  lastState = LIGHT_STATE_UNKNOWN;
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
}

void LightController_Off(int id)
{
  lastId = id;
  lastState = LIGHT_OFF;
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