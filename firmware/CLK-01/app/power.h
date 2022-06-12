#ifndef power_h
#define power_h

#include <timer2Minim.h>

class Power
{
public:
  Power() : standbyTimer(STANDBY_TIMEOUT * 1000L)
  {
  }

  void setup()
  {
  }

  void tick(bool isStandbyEnabled, bool isTimeJustChanged, int8_t mins)
  {
    if (!isStandbyEnabled)
    {
      powerOn = true;
      return;
    }
#if STANDBY_WAKEUP_ON_TIME_CHANGE
    if (isTimeJustChanged && mins % STANDBY_WAKEUP_ON_TIME_CHANGE_MINS == 0)
    {
      resetStandbyTimer();
      return;
    }
#endif
    if (standbyTimer.isReady())
    {
      powerOn = false;
      return;
    }
  }

  void resetStandbyTimer()
  {
    powerOn = true;
    standbyTimer.reset();
  }

  bool isOff()
  {
    return !powerOn;
  }

  bool isBklightOff()
  {
    return STANDBY_KEEP_BKLIGHT ? false : isOff();
  }

  bool isDotOff()
  {
    return STANDBY_KEEP_DOT ? false : isOff();
  }

private:
  timerMinim standbyTimer;
  bool powerOn;
};

Power power;

#endif
