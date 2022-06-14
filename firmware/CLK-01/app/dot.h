#ifndef dot_h
#define dot_h

#include <timer2Minim.h>
#include "power.h"
#include "nightMode.h"

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

  void turnOn()
  {
    timer.reset();
    smoothTimer.reset();
    resetSmooth();
    applyBrightness(maxBrightness);
    turnedOff = false;
  }

  void turnOff()
  {
    turnedOff = true;
    applyBrightness(0);
  }

  void tick()
  {
    if (turnedOff)
    {
      return;
    }
    updateMaxBrightness(nightMode.isNight() ? DOT_BRIGHTNESS_NIGHT : DOT_BRIGHTNESS);
#if DOT_MODE == DOT_MODE_SMOOTH
    if (smoothReady)
    {
      brightnessTick();
    }
#endif
    if (!timer.isReady())
    {
      return;
    }
#if DOT_MODE == DOT_MODE_SIMPLE
    applyBrightness(smoothBrightness);
    smoothBrightness = smoothBrightness == 0 ? maxBrightness : 0;
#endif
#if DOT_MODE == DOT_MODE_SMOOTH
    resetSmooth();
#endif
  }

private:
  timerMinim timer;
  timerMinim smoothTimer;
  byte maxBrightness;
  byte smoothStep;
  bool smoothReady;
  bool smoothUpDirection;
  int smoothBrightness;
  bool turnedOff = false;

  void updateMaxBrightness(byte newValue)
  {
    if (maxBrightness == newValue)
    {
      return;
    }
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

  void applyBrightness(byte value)
  {
    if (power.isDotOff())
    {
      value = 0;
    }
    setPWM(PIN_DOT, getPWM_CRT(value));
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
    applyBrightness(smoothBrightness);
  }
};

Dot dot(DOT_BRIGHTNESS);

#endif
