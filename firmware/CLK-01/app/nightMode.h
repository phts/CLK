#ifndef nightmode_h
#define nightmode_h

#include "indicators.h"
#include "backlight.h"
#include "dot.h"

#define NIGHT_MODE_DISABLED 0
#define NIGHT_MODE_ENABLED 1

class NightMode
{
public:
#if NIGHT_MODE == NIGHT_MODE_ENABLED
  void setup(byte hrs)
  {
    boolean isNight = (hrs >= NIGHT_START && hrs <= 23) || (hrs >= 0 && hrs < NIGHT_END);
    debug("NightMode::setup: " + String(hrs) + ", isNight=" + String(isNight));
    backlight.setNightMode(isNight);
    dot.setNightMode(isNight);
    indicators.setNightMode(isNight);
  }

  void tick(boolean isNewHour, byte hrs)
  {
    if (!isNewHour)
    {
      return;
    }
    setup(hrs);
  }
#else
  void reset(byte hrs)
  {
  }
  void tick(boolean isNewHour, byte hrs) {}
#endif
};

NightMode nightMode;

#endif
