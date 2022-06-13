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
    setEnabled(initialMode);
  }

  bool isEnabled()
  {
    return enabled;
  }

  void toggle()
  {
    setEnabled(!enabled);
  }

  void apply(byte hrs)
  {
    if (!enabled)
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
  bool enabled;
  bool forceApply = false;

  void setEnabled(bool value)
  {
    enabled = value;
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
