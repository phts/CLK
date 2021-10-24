#ifndef loop_h
#define loop_h

#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "dot.h"
#include "glitches.h"

boolean isEffectRunning = false;
TimeTickResult currentTimeTickResult;

void loop()
{
  TimeTickResult res = time.tick();
  if (res.changed && mode == MODE_CLOCK)
  {
    if (res.isNewHour)
    {
      updateBrightness();
    }
    currentTimeTickResult = res;
    isEffectRunning = true;
  }
  if (isEffectRunning)
  {
    isEffectRunning = effects.tick(currentTimeTickResult.hrs, currentTimeTickResult.mins, currentTimeTickResult.newTime);
  }
  dot.tick();
  backlight.tick();
  glitches.tick();
  buttonsTick();
  settingsTick();
  burnTick();
}

#endif
