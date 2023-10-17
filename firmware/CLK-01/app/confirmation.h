#ifndef confirmation_h
#define confirmation_h

#include <timer2Minim.h>
#include "indicators.h"
#include "dot.h"
#include "effects.h"
#include "glitches.h"
#include "time.h"

#define CONFIRMATION_TYPE_EFFECTS 0
#define CONFIRMATION_TYPE_GLITCHES 1
#define CONFIRMATION_TYPE_BKLIGHT 2
#define CONFIRMATION_TYPE_NIGHTMODE 3

class Confirmation
{
public:
  Confirmation() : stepTimer(CONFIRMATION_INTERVAL)
  {
  }

  bool isRunning()
  {
    return inProgress;
  }

  void show(byte type, byte value)
  {
    if (type == CONFIRMATION_TYPE_EFFECTS)
    {
      indicators.resetBrightness();
      indicators.turnOnAll();
      indicators.writeAll(value);
      convertTimeToArray(time.getHours(), time.getMinutes(), cachedTimeArray);
    }
    else
    {
      dot.turnOff();
      indicators.turnOffAll();
      indicators.digits[type] = value;
    }
    stepTimer.reset();
    currentType = type;
    currentValue = value;
    step = 0;
    inProgress = true;
  }

  bool tick()
  {
    if (!inProgress)
    {
      return inProgress;
    }
    if (currentType == CONFIRMATION_TYPE_EFFECTS)
    {
      bool effectsRunning = effects.tick(time.getHours(), time.getMinutes(), cachedTimeArray);
      if (!effectsRunning)
      {
        complete();
      }
      return inProgress;
    }
    if (!stepTimer.isReady())
    {
      return inProgress;
    }
    stepTimer.reset();
    step++;
    switch (step)
    {
    case 1:
      indicators.turnOn(currentType);
      break;
    case 2:
      indicators.turnOff(currentType);
      break;
    default:
      complete();
    }
    return inProgress;
  }

private:
  timerMinim stepTimer;
  bool inProgress = false;
  byte currentType;
  byte currentValue;
  byte step;
  byte cachedTimeArray[INDICATORS_AMOUNT] = {0, 0, 0, 0};

  void complete()
  {
    inProgress = false;
    indicators.writeTime(time.getHours(), time.getMinutes());
    indicators.turnOnAll();
    dot.turnOn();
    if (currentType == CONFIRMATION_TYPE_GLITCHES && currentValue == GLITCHES_ON)
    {
      glitches.forceShow();
    }
  }
};

Confirmation confirmation;

#endif
