#ifndef confirmation_h
#define confirmation_h

#include <timer2Minim.h>
#include "indicators.h"
#include "dot.h"

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
    stepTimer.reset();
    currentType = type;
    dot.turnOff();
    indicators.turnOffAll();
    indicators.digits[type] = value;
    step = 0;
    inProgress = true;
  }

  bool tick(byte hours, byte minutes)
  {
    if (!inProgress)
    {
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
      complete(hours, minutes);
    }
    return inProgress;
  }

private:
  timerMinim stepTimer;
  bool inProgress = false;
  byte currentType;
  byte step;

  void complete(byte hours, byte minutes)
  {
    inProgress = false;
    indicators.writeTime(hours, minutes);
    indicators.turnOnAll();
    dot.turnOn();
  }
};

Confirmation confirmation;

#endif
