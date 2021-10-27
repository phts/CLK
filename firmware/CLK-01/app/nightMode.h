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
  void setup(boolean initialMode)
  {
    setMode(initialMode);
  }

  boolean getMode()
  {
    return mode;
  }

  void toggle()
  {
    setMode(!mode);
  }

  void apply(byte hrs)
  {
    if (mode == NIGHT_MODE_DISABLED)
    {
      setNight(false);
      return;
    }
    boolean isNight = (hrs >= NIGHT_START && hrs <= 23) || (hrs >= 0 && hrs < NIGHT_END);
    setNight(isNight);
  }

  void tick(boolean isNewHour, byte hrs)
  {
    if (!(isNewHour || forceApply))
    {
      return;
    }
    forceApply = false;
    apply(hrs);
  }

private:
  boolean mode;
  boolean forceApply = false;

  void setMode(boolean value)
  {
    mode = value;
    forceApply = true;
  }

  void setNight(boolean value)
  {
    backlight.setNightMode(value);
    dot.setNightMode(value);
    indicators.setNightMode(value);
  }
};

NightMode nightMode;

#endif
