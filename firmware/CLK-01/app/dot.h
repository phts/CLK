#ifndef dot_h
#define dot_h

#include <timer2Minim.h>

#define DOT_MODE_SIMPLE 0
#define DOT_MODE_SMOOTH 1

class Dot
{
public:
  Dot(byte initialMaxBrightness) : timer(DOT_INTERVAL),
                                   smoothTimer(DOT_BRIGHTNESS_INTERVAL)
  {
    maxBrightness = initialMaxBrightness;
  }

  void setup()
  {
    resetBrightness();
  }

  void setNightMode(boolean isNight)
  {
    setMaxBrightness(isNight ? DOT_BRIGHTNESS_NIGHT : DOT_BRIGHTNESS);
  }

  void brightnessTick()
  {
    if (!smoothTimer.isReady())
    {
      return;
    }
    if (smoothUpDirection)
    {
      smoothBrightness += smoothStep;
      if (smoothBrightness >= maxBrightness)
      {
        smoothUpDirection = false;
        smoothBrightness = maxBrightness;
      }
    }
    else
    {
      smoothBrightness -= smoothStep;
      if (smoothBrightness <= 0)
      {
        smoothReady = false;
        smoothBrightness = 0;
      }
    }
    setPWM(PIN_DOT, getPWM_CRT(smoothBrightness));
  }

  void tick()
  {
    if (DOT_MODE == DOT_MODE_SMOOTH && smoothReady)
    {
      brightnessTick();
    }
    if (!timer.isReady())
    {
      return;
    }
    if (DOT_MODE == DOT_MODE_SIMPLE)
    {
      smoothBrightness = smoothBrightness == 0 ? maxBrightness : 0;
      setPWM(PIN_DOT, getPWM_CRT(smoothBrightness));
      return;
    }

    if (DOT_MODE == DOT_MODE_SMOOTH)
    {
      resetSmooth();
      return;
    }
  }

private:
  timerMinim timer;
  timerMinim smoothTimer;
  byte maxBrightness;
  byte smoothStep;
  boolean smoothReady;
  boolean smoothUpDirection;
  int smoothBrightness;

  void setMaxBrightness(byte newValue)
  {
    maxBrightness = newValue;
    resetBrightness();
  }

  void resetBrightness()
  {
    smoothStep = ceil((float)maxBrightness * 2 / DOT_INTERVAL * DOT_BRIGHTNESS_INTERVAL);
    if (smoothStep == 0)
    {
      smoothStep = 1;
    }
  }

  void resetSmooth()
  {
    smoothReady = true;
    smoothUpDirection = true;
    smoothBrightness = 0;
  }
};

Dot dot(DOT_BRIGHTNESS);

#endif
