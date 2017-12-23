#ifndef SRC_LIGHT_CONTROLLER_H_
#define SRC_LIGHT_CONTROLLER_H_

enum {MAX_LIGHTS = 32};
void LightController_Create();
void LightController_Destory();
void LightController_On(int id);
void LightController_Off(int id);

#endif //SRC_LIGHT_CONTROLLER_H_
