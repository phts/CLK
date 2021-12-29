#ifndef effects_h
#define effects_h

#include <timer2Minim.h>
#include "indicators.h"

#define EFFECT_NONE 0
#define EFFECT_DECAY 1
#define EFFECT_LOOP_D 2
#define EFFECT_LOOP_C 3
#define EFFECT_TRAIN 4
#define EFFECT_RUBBER 5
#define EFFECT_AMOUNT 6

#define STATE_FINISHED 0

const byte CATHOD_TO_DIGIT[] = {1, 6, 2, 7, 5, 0, 4, 9, 8, 3};
const byte DIGIT_TO_CATHOD[] = {5, 0, 2, 9, 6, 4, 1, 3, 8, 7};
const byte EFFECTS_SPEED[] = {0, 130, 50, 40, 70, 70};

class Effects
{
public:
  Effects() : timer(0) {}

  void setup(byte initialMode)
  {
    mode = initialMode;
    timer.setInterval(EFFECTS_SPEED[mode]);
  }

  byte getMode()
  {
    return mode;
  }

  void setMode(byte newMode)
  {
    mode = newMode;
    timer.setInterval(EFFECTS_SPEED[mode]);
  }

  void toggle()
  {
    byte newMode = mode + 1;
    if (newMode >= EFFECT_AMOUNT)
    {
      newMode = 0;
    }
    setMode(newMode);
  }

  bool tick(byte hrs, byte mins, byte newTime[])
  {
    switch (mode)
    {
    case EFFECT_NONE:
      return tickEffectNone(hrs, mins, newTime);
    case EFFECT_DECAY:
      return tickEffectDecay(hrs, mins, newTime);
    case EFFECT_LOOP_D:
      return tickEffectLoopDigits(hrs, mins, newTime);
    case EFFECT_LOOP_C:
      return tickEffectLoopCathodes(hrs, mins, newTime);
    case EFFECT_TRAIN:
      return tickEffectTrain(hrs, mins, newTime);
    case EFFECT_RUBBER:
      return tickEffectRubber(hrs, mins, newTime);
    }
    return false;
  }

private:
  byte mode;
  byte state;
  byte startCathode[INDICATORS_AMOUNT];
  byte endCathode[INDICATORS_AMOUNT];
  byte currentLamp;
  bool indicatorsToFlip[INDICATORS_AMOUNT];
  int decayIndicatorBrightness;
  timerMinim timer;

  bool tickEffectNone(byte hrs, byte mins, byte newTime[])
  {
    indicators.showTime(hrs, mins);
    return false;
  }

  bool tickEffectDecay(byte hrs, byte mins, byte newTime[])
  {
    if (state == STATE_FINISHED)
    {
      state = 1;
      for (byte i = 0; i < INDICATORS_AMOUNT; i++)
      {
        indicatorsToFlip[i] = indicators.digits[i] != newTime[i];
      }
      decayIndicatorBrightness = indicators.getMaxBrightness();
    }
    if (!timer.isReady())
    {
      return true;
    }
    if (state == 1)
    {
      decayIndicatorBrightness--;
      if (decayIndicatorBrightness <= 0)
      {
        state = 2;
        decayIndicatorBrightness = 0;
        indicators.showTime(hrs, mins);
      }
    }
    else
    {
      decayIndicatorBrightness++;
      if (decayIndicatorBrightness >= indicators.getMaxBrightness())
      {
        decayIndicatorBrightness = indicators.getMaxBrightness();
        state = STATE_FINISHED;
        return false;
      }
    }
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      if (indicatorsToFlip[i])
      {
        indicators.brightness[i] = decayIndicatorBrightness;
      }
    }
    return true;
  }

  bool tickEffectLoopDigits(byte hrs, byte mins, byte newTime[])
  {
    if (state == STATE_FINISHED)
    {
      state = 1;
      for (byte i = 0; i < INDICATORS_AMOUNT; i++)
      {
        indicatorsToFlip[i] = indicators.digits[i] != newTime[i];
      }
    }
    if (!timer.isReady())
    {
      return true;
    }
    byte finished = 0;
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      if (indicatorsToFlip[i])
      {
        indicators.digits[i]--;
        if (indicators.digits[i] < 0)
        {
          indicators.digits[i] = DIGITS_AMOUNT - 1;
        }
        if (indicators.digits[i] == newTime[i])
        {
          indicatorsToFlip[i] = false;
        }
      }
      else
      {
        finished++;
      }
    }
    if (finished == INDICATORS_AMOUNT)
    {
      state = STATE_FINISHED;
      return false;
    }
    return true;
  }

  bool tickEffectLoopCathodes(byte hrs, byte mins, byte newTime[])
  {
    if (state == STATE_FINISHED)
    {
      state = 1;
      for (byte i = 0; i < INDICATORS_AMOUNT; i++)
      {
        indicatorsToFlip[i] = indicators.digits[i] != newTime[i];
        if (indicatorsToFlip[i])
        {
          startCathode[i] = DIGIT_TO_CATHOD[indicators.digits[i]];
          endCathode[i] = DIGIT_TO_CATHOD[newTime[i]];
        }
      }
    }
    if (!timer.isReady())
    {
      return true;
    }
    byte finished = 0;
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      if (indicatorsToFlip[i])
      {
        if (startCathode[i] > endCathode[i])
        {
          startCathode[i]--;
          indicators.digits[i] = CATHOD_TO_DIGIT[startCathode[i]];
        }
        else if (startCathode[i] < endCathode[i])
        {
          startCathode[i]++;
          indicators.digits[i] = CATHOD_TO_DIGIT[startCathode[i]];
        }
        else
        {
          indicatorsToFlip[i] = false;
        }
      }
      else
      {
        finished++;
      }
    }
    if (finished == INDICATORS_AMOUNT)
    {
      state = STATE_FINISHED;
      return false;
    }
    return true;
  }

  bool tickEffectTrain(byte hrs, byte mins, byte newTime[])
  {
    if (state == STATE_FINISHED)
    {
      state = 1;
      currentLamp = 0;
      timer.reset();
    }
    if (!timer.isReady())
    {
      return true;
    }
    if (state == 1)
    {
      for (byte i = 3; i > currentLamp; i--)
      {
        indicators.digits[i] = indicators.digits[i - 1];
      }
      indicators.turnOff(currentLamp);
      currentLamp++;
      if (currentLamp >= INDICATORS_AMOUNT)
      {
        state = 2;
        currentLamp = 0;
      }
    }
    else
    {
      for (byte i = currentLamp; i > 0; i--)
      {
        indicators.digits[i] = indicators.digits[i - 1];
      }
      indicators.digits[0] = newTime[3 - currentLamp];
      indicators.turnOn(currentLamp);
      currentLamp++;
      if (currentLamp >= INDICATORS_AMOUNT)
      {
        state = STATE_FINISHED;
        return false;
      }
    }
    return true;
  }

  bool tickEffectRubber(byte hrs, byte mins, byte newTime[])
  {
    if (state == STATE_FINISHED)
    {
      state = 1;
      timer.reset();
    }
    if (!timer.isReady())
    {
      return true;
    }
    switch (state)
    {
    case 1:
      indicators.turnOff(3);
      break;
    case 2:
      indicators.turnOff(2);
      indicators.digits[3] = indicators.digits[2];
      indicators.turnOn(3);
      break;
    case 3:
      indicators.turnOff(3);
      break;
    case 4:
      indicators.turnOff(1);
      indicators.digits[2] = indicators.digits[1];
      indicators.turnOn(2);
      break;
    case 5:
      indicators.turnOff(2);
      indicators.digits[3] = indicators.digits[1];
      indicators.turnOn(3);
      break;
    case 6:
      indicators.turnOff(3);
      break;
    case 7:
      indicators.turnOff(0);
      indicators.digits[1] = indicators.digits[0];
      indicators.turnOn(1);
      break;
    case 8:
      indicators.turnOff(1);
      indicators.digits[2] = indicators.digits[0];
      indicators.turnOn(2);
      break;
    case 9:
      indicators.turnOff(2);
      indicators.digits[3] = indicators.digits[0];
      indicators.turnOn(3);
      break;
    case 10:
      indicators.turnOff(3);
      break;
    case 11:
      indicators.digits[0] = newTime[3];
      indicators.turnOn(0);
      break;
    case 12:
      indicators.turnOff(0);
      indicators.digits[1] = newTime[3];
      indicators.turnOn(1);
      break;
    case 13:
      indicators.turnOff(1);
      indicators.digits[2] = newTime[3];
      indicators.turnOn(2);
      break;
    case 14:
      indicators.turnOff(2);
      indicators.digits[3] = newTime[3];
      indicators.turnOn(3);
      break;
    case 15:
      indicators.digits[0] = newTime[2];
      indicators.turnOn(0);
      break;
    case 16:
      indicators.turnOff(0);
      indicators.digits[1] = newTime[2];
      indicators.turnOn(1);
      break;
    case 17:
      indicators.turnOff(1);
      indicators.digits[2] = newTime[2];
      indicators.turnOn(2);
      break;
    case 18:
      indicators.digits[0] = newTime[1];
      indicators.turnOn(0);
      break;
    case 19:
      indicators.turnOff(0);
      indicators.digits[1] = newTime[1];
      indicators.turnOn(1);
      break;
    case 20:
      indicators.digits[0] = newTime[0];
      indicators.turnOn(0);
      break;
    case 21:
      state = STATE_FINISHED;
      return false;
    }
    state++;
    return true;
  }
};

Effects effects;

#endif
