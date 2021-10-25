#ifndef effects_h
#define effects_h

#include <timer2Minim.h>

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
  Effects() : flipTimer(0)
  {
  }

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

  boolean tick(byte hrs, byte mins, byte *newTime)
  {
    if (mode == EFFECT_NONE)
    {
      showTime(hrs, mins);
      return false;
    }

    else if (mode == EFFECT_DECAY)
    {
      if (!flipInProgress)
      {
        flipInProgress = true;
        for (byte i = 0; i < 4; i++)
        {
          indicatorsToFlip[i] = indicatorDigits[i] != newTime[i];
        }
        decayIndicatorBrightness = indicatorMaxBrightness;
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
            showTime(hrs, mins);
          }
        }
        else
        {
          decayIndicatorBrightness++;
          if (decayIndicatorBrightness >= indicatorMaxBrightness)
          {
            decayDirection = false;
            decayIndicatorBrightness = indicatorMaxBrightness;
            flipInProgress = false;
            return false;
          }
        }
        for (byte i = 0; i < 4; i++)
        {
          if (indicatorsToFlip[i])
          {
            indicatorBrightness[i] = decayIndicatorBrightness;
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
          indicatorsToFlip[i] = indicatorDigits[i] != newTime[i];
        }
      }
      if (flipTimer.isReady())
      {
        byte flipCounter = 0;
        for (byte i = 0; i < 4; i++)
        {
          if (indicatorsToFlip[i])
          {
            indicatorDigits[i]--;
            if (indicatorDigits[i] < 0)
            {
              indicatorDigits[i] = 9;
            }
            if (indicatorDigits[i] == newTime[i])
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
          indicatorsToFlip[i] = indicatorDigits[i] != newTime[i];
          if (indicatorsToFlip[i])
          {
            for (byte c = 0; c < 10; c++)
            {
              if (indicatorDigits[i] == CATHOD_TO_DIGIT[c])
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
              indicatorDigits[i] = CATHOD_TO_DIGIT[startCathode[i]];
            }
            else if (startCathode[i] < endCathode[i])
            {
              startCathode[i]++;
              indicatorDigits[i] = CATHOD_TO_DIGIT[startCathode[i]];
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
            indicatorDigits[i] = indicatorDigits[i - 1];
          }
          anodeStates[currentLamp] = 0;
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
            indicatorDigits[i] = indicatorDigits[i - 1];
          }
          indicatorDigits[0] = newTime[3 - currentLamp];
          anodeStates[currentLamp] = 1;
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
          anodeStates[3] = 0;
          break;
        case 2:
          anodeStates[2] = 0;
          indicatorDigits[3] = indicatorDigits[2];
          anodeStates[3] = 1;
          break;
        case 3:
          anodeStates[3] = 0;
          break;
        case 4:
          anodeStates[1] = 0;
          indicatorDigits[2] = indicatorDigits[1];
          anodeStates[2] = 1;
          break;
        case 5:
          anodeStates[2] = 0;
          indicatorDigits[3] = indicatorDigits[1];
          anodeStates[3] = 1;
          break;
        case 6:
          anodeStates[3] = 0;
          break;
        case 7:
          anodeStates[0] = 0;
          indicatorDigits[1] = indicatorDigits[0];
          anodeStates[1] = 1;
          break;
        case 8:
          anodeStates[1] = 0;
          indicatorDigits[2] = indicatorDigits[0];
          anodeStates[2] = 1;
          break;
        case 9:
          anodeStates[2] = 0;
          indicatorDigits[3] = indicatorDigits[0];
          anodeStates[3] = 1;
          break;
        case 10:
          anodeStates[3] = 0;
          break;
        case 11:
          indicatorDigits[0] = newTime[3];
          anodeStates[0] = 1;
          break;
        case 12:
          anodeStates[0] = 0;
          indicatorDigits[1] = newTime[3];
          anodeStates[1] = 1;
          break;
        case 13:
          anodeStates[1] = 0;
          indicatorDigits[2] = newTime[3];
          anodeStates[2] = 1;
          break;
        case 14:
          anodeStates[2] = 0;
          indicatorDigits[3] = newTime[3];
          anodeStates[3] = 1;
          break;
        case 15:
          indicatorDigits[0] = newTime[2];
          anodeStates[0] = 1;
          break;
        case 16:
          anodeStates[0] = 0;
          indicatorDigits[1] = newTime[2];
          anodeStates[1] = 1;
          break;
        case 17:
          anodeStates[1] = 0;
          indicatorDigits[2] = newTime[2];
          anodeStates[2] = 1;
          break;
        case 18:
          indicatorDigits[0] = newTime[1];
          anodeStates[0] = 1;
          break;
        case 19:
          anodeStates[0] = 0;
          indicatorDigits[1] = newTime[1];
          anodeStates[1] = 1;
          break;
        case 20:
          indicatorDigits[0] = newTime[0];
          anodeStates[0] = 1;
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
