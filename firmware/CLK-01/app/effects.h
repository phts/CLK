#ifndef effects_h
#define effects_h

#include <timer2Minim.h>
#include "indicators.h"

#define EFFECT_NONE 0
#define EFFECT_DECAY 1
#define EFFECT_LOOP_DIGITS 2
#define EFFECT_LOOP_DIGITS_REV 3
#define EFFECT_LOOP_CATHODES 4
#define EFFECT_LOOP_CATHODES_LONG 5
#define EFFECT_PINGPONG_CATHODES 6
#define EFFECT_TRAIN 7
#define EFFECT_RUBBER 8
#define EFFECT_AMOUNT 9

#define STATE_FINISHED 0

const byte CATHOD_TO_DIGIT[] = {1, 6, 2, 7, 5, 0, 4, 9, 8, 3};
const byte DIGIT_TO_CATHOD[] = {5, 0, 2, 9, 6, 4, 1, 3, 8, 7};
const byte EFFECTS_SPEED[] = {0, 130, 70, 70, 50, 50, 50, 70, 70};

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
    case EFFECT_LOOP_DIGITS:
      return tickEffectLoopDigits(hrs, mins, newTime);
    case EFFECT_LOOP_DIGITS_REV:
      return tickEffectLoopDigitsRev(hrs, mins, newTime);
    case EFFECT_LOOP_CATHODES:
      return tickEffectLoopCathodes(hrs, mins, newTime, 0);
    case EFFECT_LOOP_CATHODES_LONG:
      return tickEffectLoopCathodes(hrs, mins, newTime, 1);
    case EFFECT_PINGPONG_CATHODES:
      return tickEffectPingpongCathodes(hrs, mins, newTime);
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
  byte indicatorsToFlip[INDICATORS_AMOUNT];
  byte cathodeLoopStates[INDICATORS_AMOUNT];
  int decayIndicatorBrightness;
  timerMinim timer;

  bool tickEffectNone(byte hrs, byte mins, byte newTime[])
  {
    indicators.writeTime(hrs, mins);
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
        indicators.writeTime(hrs, mins);
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
        indicators.setBrightness(i, decayIndicatorBrightness);
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
        indicatorsToFlip[i] = indicators.digits[i] != newTime[i] ? 2 : 0;
      }
    }
    if (!timer.isReady())
    {
      return true;
    }
    byte finished = 0;
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      if (!indicatorsToFlip[i])
      {
        finished++;
        continue;
      }
      indicators.digits[i]++;
      if (indicators.digits[i] >= DIGITS_AMOUNT)
      {
        indicators.digits[i] = 0;
      }
      if (indicators.digits[i] == newTime[i])
      {
        indicatorsToFlip[i]--;
      }
    }
    if (finished == INDICATORS_AMOUNT)
    {
      state = STATE_FINISHED;
      return false;
    }
    return true;
  }

  bool tickEffectLoopDigitsRev(byte hrs, byte mins, byte newTime[])
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
      if (!indicatorsToFlip[i])
      {
        finished++;
        continue;
      }
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
    if (finished == INDICATORS_AMOUNT)
    {
      state = STATE_FINISHED;
      return false;
    }
    return true;
  }

  bool tickEffectLoopCathodes(byte hrs, byte mins, byte newTime[], byte loops)
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
          endCathode[i] += (startCathode[i] > endCathode[i] ? 2 * DIGITS_AMOUNT : DIGITS_AMOUNT) * loops;
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
      if (!indicatorsToFlip[i])
      {
        finished++;
        continue;
      }
      if (startCathode[i] > endCathode[i])
      {
        startCathode[i]--;
        indicators.digits[i] = CATHOD_TO_DIGIT[startCathode[i]];
      }
      else if (startCathode[i] < endCathode[i])
      {
        startCathode[i]++;
        indicators.digits[i] = CATHOD_TO_DIGIT[startCathode[i] % DIGITS_AMOUNT];
      }
      else
      {
        indicatorsToFlip[i] = false;
      }
    }
    if (finished == INDICATORS_AMOUNT)
    {
      state = STATE_FINISHED;
      return false;
    }
    return true;
  }

  bool tickEffectPingpongCathodes(byte hrs, byte mins, byte newTime[])
  {
    if (state == STATE_FINISHED)
    {
      state = 1;
      for (byte i = 0; i < INDICATORS_AMOUNT; i++)
      {
        cathodeLoopStates[i] = 0;
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
      if (!indicatorsToFlip[i])
      {
        finished++;
        continue;
      }
      if (cathodeLoopStates[i] == 0)
      {
        startCathode[i]++;
        if (startCathode[i] >= DIGITS_AMOUNT)
        {
          cathodeLoopStates[i] = 1;
          startCathode[i] = DIGITS_AMOUNT - 1;
          continue;
        }
      }
      else if (cathodeLoopStates[i] == 1)
      {
        startCathode[i]--;
        if (startCathode[i] <= 0)
        {
          cathodeLoopStates[i] = 2;
          startCathode[i] = 0;
          continue;
        }
      }
      else
      {
        if (startCathode[i] == endCathode[i])
        {
          indicatorsToFlip[i] = false;
        }
        else
        {
          startCathode[i]++;
        }
      }

      indicators.digits[i] = CATHOD_TO_DIGIT[startCathode[i]];
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
