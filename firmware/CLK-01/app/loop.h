#ifndef loop_h
#define loop_h

#include "effects.h"
#include "backlight.h"
#include "dot.h"
#include "glitches.h"

void loop()
{
  timeTick();
  if (timeJustChanged && mode == MODE_CLOCK)
  {
    effects.tick();
  }
  dot.tick();
  backlight.tick();
  glitches.tick();
  buttonsTick();
  settingsTick();
  burnTick();
}

#endif
