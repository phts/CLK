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

const byte CATHOD_TO_DIGIT[] = {1, 6, 2, 7, 5, 0, 4, 9, 8, 3};
const byte EFFECTS_SPEED[] = {0, 130, 50, 40, 70, 70};

class Effects
{
public:
  Effects() : flipTimer(0) {}

  void setup(byte initialMode)
  {
    mode = initialMode;
    flipTimer.setInterval(EFFECTS_SPEED[mode]);
  }

  byte getMode()
  {
    return mode;
  }

  void setMode(byte newMode)
  {
    mode = newMode;
    flipTimer.setInterval(EFFECTS_SPEED[mode]);
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

  boolean tick(byte hrs, byte mins, byte newTime[])
  {
    if (mode == EFFECT_NONE)
    {
      indicators.showTime(hrs, mins);
      return false;
    }

    else if (mode == EFFECT_DECAY)
    {
      if (!flipInProgress)
      {
        flipInProgress = true;
        for (byte i = 0; i < 4; i++)
        {
          indicatorsToFlip[i] = indicators.digits[i] != newTime[i];
        }
        decayIndicatorBrightness = indicators.getMaxBrightness();
      }
      if (flipTimer.isReady())
      {
        if (!decayDirection)
        {
          decayIndicatorBrightness--;
          if (decayIndicatorBrightness <= 0)
          {
            decayDirection = true;
            decayIndicatorBrightness = 0;
            indicators.showTime(hrs, mins);
          }
        }
        else
        {
          decayIndicatorBrightness++;
          if (decayIndicatorBrightness >= indicators.getMaxBrightness())
          {
            decayDirection = false;
            decayIndicatorBrightness = indicators.getMaxBrightness();
            flipInProgress = false;
            return false;
          }
        }
        for (byte i = 0; i < 4; i++)
        {
          if (indicatorsToFlip[i])
          {
            indicators.brightness[i] = decayIndicatorBrightness;
          }
        }
      }
    }

    else if (mode == EFFECT_LOOP_D)
    {
      if (!flipInProgress)
      {
        flipInProgress = true;
        for (byte i = 0; i < 4; i++)
        {
          indicatorsToFlip[i] = indicators.digits[i] != newTime[i];
        }
      }
      if (flipTimer.isReady())
      {
        byte flipCounter = 0;
        for (byte i = 0; i < 4; i++)
        {
          if (indicatorsToFlip[i])
          {
            indicators.digits[i]--;
            if (indicators.digits[i] < 0)
            {
              indicators.digits[i] = 9;
            }
            if (indicators.digits[i] == newTime[i])
            {
              indicatorsToFlip[i] = false;
            }
          }
          else
          {
            flipCounter++;
          }
        }
        if (flipCounter == 4)
        {
          flipInProgress = false;
          return false;
        }
      }
    }

    else if (mode == EFFECT_LOOP_C)
    {
      if (!flipInProgress)
      {
        flipInProgress = true;
        for (byte i = 0; i < 4; i++)
        {
          indicatorsToFlip[i] = indicators.digits[i] != newTime[i];
          if (indicatorsToFlip[i])
          {
            for (byte c = 0; c < 10; c++)
            {
              if (indicators.digits[i] == CATHOD_TO_DIGIT[c])
              {
                startCathode[i] = c;
              }
              if (newTime[i] == CATHOD_TO_DIGIT[c])
              {
                endCathode[i] = c;
              }
            }
          }
        }
      }
      if (flipTimer.isReady())
      {
        byte flipCounter = 0;
        for (byte i = 0; i < 4; i++)
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
            flipCounter++;
          }
        }
        if (flipCounter == 4)
        {
          flipInProgress = false;
          return false;
        }
      }
    }

    else if (mode == EFFECT_TRAIN)
    {
      if (!flipInProgress)
      {
        flipInProgress = true;
        currentLamp = 0;
        trainLeaving = true;
        flipTimer.reset();
      }
      if (flipTimer.isReady())
      {
        if (trainLeaving)
        {
          for (byte i = 3; i > currentLamp; i--)
          {
            indicators.digits[i] = indicators.digits[i - 1];
          }
          indicators.turnOff(currentLamp);
          currentLamp++;
          if (currentLamp >= 4)
          {
            trainLeaving = false;
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
          if (currentLamp >= 4)
          {
            flipInProgress = false;
            return false;
          }
        }
      }
    }

    else if (mode == EFFECT_RUBBER)
    {
      if (!flipInProgress)
      {
        flipInProgress = true;
        flipEffectStages = 0;
        flipTimer.reset();
      }
      if (flipTimer.isReady())
      {
        switch (flipEffectStages++)
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
          flipInProgress = false;
          return false;
        }
      }
    }

    return true;
  }

private:
  byte mode;
  boolean flipInProgress;
  bool trainLeaving;
  byte startCathode[4];
  byte endCathode[4];
  byte currentLamp;
  byte flipEffectStages;
  boolean indicatorsToFlip[4];
  boolean decayDirection;
  int decayIndicatorBrightness;
  timerMinim flipTimer;
};

Effects effects;

#endif
