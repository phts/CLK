#ifndef power_h
#define power_h

#include <timer2Minim.h>
#include "time.h"
#include "nightMode.h"

#define POWER_OFF 0
#define POWER_ON 1
#define POWER_ALWAYS_ON 2

class Power
{
public:
  Power() : standbyTimer(STANDBY_TIMEOUT * 1000L)
  {
  }

  void setup()
  {
  }

  void tick(bool isStandbyEnabled, TimeTickResult time)
  {
    if (!isStandbyEnabled)
    {
      state = POWER_ALWAYS_ON;
      return;
    }
    if (nightMode.isNight() && nightMode.isNightlight())
    {
      state = POWER_ON;
      return;
    }
#if STANDBY_WAKEUP_RANDOM
    if (time.isNewHour)
    {
      debug(F("Wakeup on minutes:"));
      for (byte i = 0; i < wakeupRandomMinutesSize; i++)
      {
        wakeupRandomMinutes[i] = random(60 / wakeupRandomMinutesSize * i + 1, 60 / wakeupRandomMinutesSize * (i + 1));
        debug(wakeupRandomMinutes[i]);
      }
    }
#endif
#if STANDBY_WAKEUP_ON_TIME_CHANGE
    if (!nightMode.isNightlight() && time.changed && time.mins % STANDBY_WAKEUP_ON_TIME_CHANGE_MINS == 0)
    {
      if (!STANDBY_NIGHT_SLEEP || !nightMode.isNight())
      {
        resetStandbyTimer();
        return;
      }
    }
#endif
#if STANDBY_WAKEUP_RANDOM
    if (!nightMode.isNightlight() && time.changed)
    {
      if (!STANDBY_NIGHT_SLEEP || !nightMode.isNight())
      {
        for (byte i = 0; i < wakeupRandomMinutesSize; i++)
        {
          if (time.mins == wakeupRandomMinutes[i])
          {
            resetStandbyTimer();
            return;
          }
        }
      }
    }
#endif
    if (standbyTimer.isReady())
    {
      if (state != POWER_OFF)
      {
        state = POWER_OFF;
        debug(F("Enter standby"));
      }
      return;
    }
  }

  void resetStandbyTimer()
  {
    if (state != POWER_ON)
    {
      debug(F("Exit standby"));
    }
    else
    {
      debug(F("Reset standby timer"));
    }
    state = POWER_ON;
    standbyTimer.reset();
  }

  bool isOff()
  {
    if (state == POWER_ALWAYS_ON)
    {
      return false;
    }
    return !state;
  }

  bool isBklightOff()
  {
    if (isOff() && STANDBY_NIGHT_SLEEP && nightMode.isNight())
    {
      return true;
    }
    return STANDBY_KEEP_BKLIGHT ? false : isOff();
  }

  bool isDotOff()
  {
    if (isOff() && STANDBY_NIGHT_SLEEP && nightMode.isNight())
    {
      return true;
    }
    return STANDBY_KEEP_DOT ? false : isOff();
  }

private:
  timerMinim standbyTimer;
  byte state = POWER_ON;
#if STANDBY_WAKEUP_RANDOM
  byte wakeupRandomMinutes[STANDBY_WAKEUP_RANDOM_TIMES];
  byte wakeupRandomMinutesSize = sizeof(wakeupRandomMinutes);
#endif
};

Power power;

#endif
