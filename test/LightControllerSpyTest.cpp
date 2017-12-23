#include "gtest/gtest.h"
extern "C" {
  #include "LightControllerSpy.h"
}

namespace light_controller_spy_test{
  class LightControllerSpyTest : public ::testing::Test
  {
    virtual void SetUp()
    {
      LightController_Create();
    }

    virtual void TearDown()
    {
      LightController_Destory();
    }
  };


  TEST_F(LightControllerSpyTest, Create)
  {
    EXPECT_EQ(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    EXPECT_EQ(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
  }

  TEST_F(LightControllerSpyTest, RemenberTheLastLightIdControlled)
  {
    LightController_On(10);
    EXPECT_EQ(10, LightControllerSpy_GetLastId());
    EXPECT_EQ(LIGHT_ON, LightControllerSpy_GetLastState());
  }

  TEST_F(LightControllerSpyTest, RememberAllLightStates)
  {
    LightController_On(0);
    LightController_Off(31);
    EXPECT_EQ(LIGHT_ON, LightControllerSpy_GetLightState(0));
    EXPECT_EQ(LIGHT_OFF, LightControllerSpy_GetLightState(31));
  }

}