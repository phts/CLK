#ifndef loop_h
#define loop_h

#include "effects.h"

void loop()
{
  timeTick();
  if (timeJustChanged && mode == MODE_CLOCK)
  {
    effects.tick();
  }
  dotTick();
  bklightBrightnessTick();
  if (currentGlitchesMode == GLITCHES_ON)
  {
    glitchTick();
  }
  buttonsTick();
  settingsTick();
  burnTick();
}

#endif
