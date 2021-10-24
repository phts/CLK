#ifndef loop_h
#define loop_h

#include "effects.h"
#include "backlight.h"
#include "dot.h"

void loop()
{
  timeTick();
  if (timeJustChanged && mode == MODE_CLOCK)
  {
    effects.tick();
  }
  dot.tick();
  backlight.tick();
  if (currentGlitchesMode == GLITCHES_ON)
  {
    glitchTick();
  }
  buttonsTick();
  settingsTick();
  burnTick();
}

#endif
