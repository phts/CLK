#ifndef loop_h
#define loop_h

#include "time.h"
#include "indicators.h"
#include "effects.h"
#include "backlight.h"
#include "dot.h"
#include "glitches.h"
#include "control.h"
#include "nightMode.h"

boolean isEffectRunning = false;
TimeTickResult cachedTimeResult;
byte cachedNewTime[] = {0, 0, 0, 0};

void loop()
{
  TimeTickResult res = time.tick();
  if (res.changed && control.isClockMode())
  {
    cachedTimeResult = res;
    convertTimeToArray(res.hrs, res.mins, cachedNewTime);
    isEffectRunning = true;
  }
  if (isEffectRunning)
  {
    isEffectRunning = effects.tick(cachedTimeResult.hrs, cachedTimeResult.mins, cachedNewTime);
  }
  dot.tick();
  backlight.tick();
  glitches.tick(res.secs);
  control.tick();
  indicators.burnTick(res.isNewHour, res.mins, res.secs, control.isClockMode());
  nightMode.tick(res.isNewHour, res.hrs);
}

#endif
