#ifndef loop_h
#define loop_h

#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "dot.h"
#include "glitches.h"
#include "control.h"

boolean isEffectRunning = false;
TimeTickResult cachedTimeResult;
byte cachedNewTime[] = {0, 0, 0, 0};

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
    cachedTimeResult = res;
    convertTimeToArray(res.hrs, res.mins, cachedNewTime);
    isEffectRunning = true;
  }
  if (isEffectRunning)
  {
    debug("isEffectRunning" + String(isEffectRunning));
    isEffectRunning = effects.tick(cachedTimeResult.hrs, cachedTimeResult.mins, cachedNewTime);
  }
  dot.tick();
  backlight.tick();
  glitches.tick();
  control.tick();
  burnTick();
}

#endif
