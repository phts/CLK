#ifndef glitches_h
#define glitches_h

#include <timer2Minim.h>
#include "indicators.h"

#define GLITCHES_OFF 0
#define GLITCHES_ON 1

class Glitches
{
public:
  Glitches() : timer(1000) {}

  void setup(bool initialMode)
  {
    mode = initialMode;
    resetTimer();
  }

  void toggle()
  {
    setMode(!mode);
  }

  bool getMode()
  {
    return mode;
  }

  void setMode(byte newValue)
  {
    mode = newValue;
  }

  void tick(byte secs)
  {
    if (mode != GLITCHES_ON)
    {
      return;
    }
    if (!isRunning && secs > 7 && secs < 55)
    {
      if (timer.isReady())
      {
        resetState();
        resetStepTimer();
      }
    }
    else if (isRunning && (timer.isReady() || forceRun))
    {
      forceRun = false;
      indicators.setBrightness(targetIndicator, indicatorState * indicators.getMaxBrightness());
      indicatorState = !indicatorState;
      resetStepTimer();
      count++;
      if (count > maxAmount)
      {
        resetTimer();
        isRunning = false;
        indicators.setBrightness(targetIndicator, indicators.getMaxBrightness());
      }
    }
  }

  void forceShow()
  {
    forceRun = true;
    resetState();
  }

private:
  timerMinim timer;
  bool mode;
  byte count;
  byte maxAmount;
  byte targetIndicator;
  bool isRunning;
  bool indicatorState;
  bool forceRun;

  void resetState()
  {
    isRunning = true;
    indicatorState = 0;
    count = 0;
    maxAmount = random(4, 9);
    targetIndicator = random(0, 4);
  }

  void resetTimer()
  {
    timer.setInterval(random(GLITCH_MIN_INTERVAL * 1000L, GLITCH_MAX_INTERVAL * 1000L));
  }

  void resetStepTimer()
  {
    timer.setInterval(random(2, 6) * 20);
  }
};

Glitches glitches;

#endif
