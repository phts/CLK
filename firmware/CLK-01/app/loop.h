#ifndef loop_h
#define loop_h

#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "dot.h"
#include "glitches.h"
#include "control.h"

boolean isEffectRunning = false;
TimeTickResult currentTimeTickResult;

void loop()
{
  TimeTickResult res = time.tick();
  if (res.changed && control.isClockMode())
  {
    debug("res.changed" + String(res.changed));
    debug("res.isNewHour" + String(res.isNewHour));
    debug("res.hrs" + String(res.hrs));
    debug("res.mins" + String(res.mins));
    if (res.isNewHour)
    {
      updateBrightness();
    }
    currentTimeTickResult = res;
    isEffectRunning = true;
  }
  if (isEffectRunning)
  {
    debug("isEffectRunning" + String(isEffectRunning));
    isEffectRunning = effects.tick(currentTimeTickResult.hrs, currentTimeTickResult.mins, currentTimeTickResult.newTime);
  }
  dot.tick();
  backlight.tick();
  glitches.tick();
  control.tick();
  burnTick();
}

#endif
