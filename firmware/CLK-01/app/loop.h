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
#include "power.h"

bool isEffectRunning = false;
TimeTickResult cachedTimeResult;
byte cachedNewTime[] = {0, 0, 0, 0};

void loop()
{
  TimeTickResult timeRes = time.tick();
  if (timeRes.changed && control.isClockMode())
  {
    debug(F("Is new hour"), timeRes.isNewHour);
    debug(F("Hrs"), timeRes.hrs);
    debug(F("Mins"), timeRes.mins);
    cachedTimeResult = timeRes;
    convertTimeToArray(timeRes.hrs, timeRes.mins, cachedNewTime);
    isEffectRunning = true;
  }
  control.tick();
  power.tick(control.isStandbyEnabled(), timeRes.changed, timeRes.mins);
  if (isEffectRunning)
  {
    isEffectRunning = effects.tick(cachedTimeResult.hrs, cachedTimeResult.mins, cachedNewTime);
  }
  dot.tick();
  backlight.tick();
  if (control.isClockMode())
  {
    glitches.tick(timeRes.secs);
  }
  indicators.tick(timeRes.isNewHour, timeRes.mins, timeRes.secs, control.isClockMode());
  nightMode.tick(timeRes.isNewHour, timeRes.hrs);
}

#endif
