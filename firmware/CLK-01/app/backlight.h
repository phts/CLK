#ifndef backlight_h
#define backlight_h

#include <timer2Minim.h>
#include "power.h"
#include "nightMode.h"

#define BKLIGHT_OFF 0
#define BKLIGHT_ON 1
#define BKLIGHT_ON_60 2
#define BKLIGHT_ON_30 3
#define BKLIGHT_FLASH 4
#define BKLIGHT_AMOUNT 5

class Backlight
{
public:
  Backlight(byte initialMaxBrightness) : brightnessTimer(30)
  {
    maxBrightness = initialMaxBrightness;
  }

  void setup(byte initialMode)
  {
    setMode(initialMode);
    resetFlashBrightnessTimer();
  }

  byte getMode()
  {
    return mode;
  }

  void setMode(byte newMode)
  {
    mode = newMode;
    resetBrightness();
  }

  void reset()
  {
    setMode(mode);
  }

  void toggle()
  {
    byte newMode = mode + 1;
    if (newMode >= BKLIGHT_AMOUNT)
    {
      newMode = 0;
    }
    setMode(newMode);
  }

  void tick()
  {
    if (power.isBklightOff())
    {
      turnOff();
    }
    else
    {
      updateMaxBrightness(nightMode.isNight() ? BKLIGHT_BRIGHTNESS_NIGHT : BKLIGHT_BRIGHTNESS);
    }
    if (mode != BKLIGHT_FLASH)
    {
      return;
    }
    if (!brightnessTimer.isReady())
    {
      return;
    }
    if (maxBrightness > 0)
    {
      if (flashDirection)
      {
        if (!flashStarted)
        {
          flashStarted = true;
          resetFlashBrightnessTimer();
        }
        currentFlashBrightness += BKLIGHT_STEPS;
        if (currentFlashBrightness >= maxBrightness)
        {
          flashDirection = false;
          currentFlashBrightness = maxBrightness;
        }
      }
      else
      {
        currentFlashBrightness -= BKLIGHT_STEPS;
        if (currentFlashBrightness <= BKLIGHT_MIN_BRIGHTNESS)
        {
          flashDirection = true;
          currentFlashBrightness = BKLIGHT_MIN_BRIGHTNESS;
          brightnessTimer.setInterval(BKLIGHT_DELAY);
          flashStarted = false;
        }
      }
      setPWM(PIN_BKLIGHT, getPWM_CRT(currentFlashBrightness));
    }
    else
    {
      turnOff();
    }
  }

private:
  byte mode;
  byte maxBrightness;
  bool flashStarted;
  bool flashDirection;
  int currentFlashBrightness;
  timerMinim brightnessTimer;

  void updateMaxBrightness(byte newValue)
  {
    if (maxBrightness == newValue)
    {
      return;
    }
    maxBrightness = newValue;
    resetBrightness();
  }

  void resetFlashBrightnessTimer()
  {
    if (maxBrightness > 0)
    {
      brightnessTimer.setInterval((float)BKLIGHT_STEPS / maxBrightness / 2 * BKLIGHT_PERIOD);
    }
  }

  void resetBrightness()
  {
    if (mode == BKLIGHT_ON)
    {
      setPWM(PIN_BKLIGHT, maxBrightness);
    }
    else if (mode == BKLIGHT_ON_30)
    {
      setPWM(PIN_BKLIGHT, maxBrightness / 3);
    }
    else if (mode == BKLIGHT_ON_60)
    {
      setPWM(PIN_BKLIGHT, maxBrightness / 3 * 2);
    }
    else if (mode == BKLIGHT_OFF)
    {
      turnOff();
    }
    resetFlashBrightnessTimer();
  }

  void turnOff()
  {
    digitalWrite(PIN_BKLIGHT, 0);
  }
};

Backlight backlight(BKLIGHT_BRIGHTNESS);

#endif
