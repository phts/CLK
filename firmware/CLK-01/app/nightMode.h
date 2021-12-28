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
  void setup(bool initialMode)
  {
    setMode(initialMode);
  }

  bool getMode()
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
    bool isNight = (hrs >= NIGHT_START && hrs <= 23) || (hrs >= 0 && hrs < NIGHT_END);
    setNight(isNight);
  }

  void tick(bool isNewHour, byte hrs)
  {
    if (!(isNewHour || forceApply))
    {
      return;
    }
    forceApply = false;
    apply(hrs);
  }

private:
  bool mode;
  bool forceApply = false;

  void setMode(bool value)
  {
    mode = value;
    forceApply = true;
  }

  void setNight(bool value)
  {
    backlight.setNightMode(value);
    dot.setNightMode(value);
    indicators.setNightMode(value);
  }
};

NightMode nightMode;

#endif
