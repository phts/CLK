#ifndef indicators_h
#define indicators_h

#include <timer2Minim.h>
#include "power.h"
#include "nightMode.h"

#define INDICATOR_TURNED_OFF 0
#define INDICATOR_TURNED_ON 1

class Indicators
{
public:
  volatile int8_t digits[INDICATORS_AMOUNT]; // 0--9

  Indicators()
  {
  }

  void setup()
  {
    resetBrightness();
  }

  int8_t getBrightness(byte indicator)
  {
    if (power.isOff())
    {
      return 0;
    }
    return brightness[indicator];
  }

  void setBrightness(byte indicator, int8_t value)
  {
    brightness[indicator] = value;
  }

  void resetBrightness()
  {
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      brightness[i] = maxBrightness;
    }
  }

  byte getMaxBrightness()
  {
    return maxBrightness;
  }

  void writeTime(byte hours, byte minutes)
  {
    convertTimeToArray(hours, minutes, digits);
  }

  void writeAll(byte digit)
  {
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      digits[i] = digit;
    }
  }

  bool isOn(byte n)
  {
    if (power.isOff())
    {
      return false;
    }
    return anodeStates[n];
  }

  void turnOn(byte n)
  {
    anodeStates[n] = INDICATOR_TURNED_ON;
  }

  void turnOff(byte n)
  {
    anodeStates[n] = INDICATOR_TURNED_OFF;
  }

  void turnOnAll()
  {
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      anodeStates[i] = INDICATOR_TURNED_ON;
    }
  }

  void turnOffAll()
  {
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      anodeStates[i] = INDICATOR_TURNED_OFF;
    }
  }

  void tick(bool isNewHour, byte mins, byte secs, bool isBurnEnabled)
  {
    updateMaxBrightness(nightMode.isNight() ? INDICATOR_BRIGHTNESS_NIGHT : INDICATOR_BRIGHTNESS);
    if (burnInProgress)
    {
      return;
    }
    if (isNewHour)
    {
      debug(F("Burn on minutes:"));
      for (byte i = 0; i < burnOnMinutesSize; i++)
      {
        burnOnMinutes[i] = random(60 / burnOnMinutesSize * i + 5, 60 / burnOnMinutesSize * (i + 1) - 5 + 1);
        debug(burnOnMinutes[i]);
      }
    }
    if (isBurnEnabled)
    {
      for (byte i = 0; i < burnOnMinutesSize; i++)
      {
        if (mins == burnOnMinutes[i] && secs >= 15)
        {
          burnInProgress = true;
          burnOnMinutes[i] = -1;
          burnIndicators();
          burnInProgress = false;
          break;
        }
      }
    }
  }

private:
  volatile int8_t brightness[INDICATORS_AMOUNT]; // 0--24
  byte maxBrightness;
  bool anodeStates[INDICATORS_AMOUNT] = {1, 1, 1, 1};
  bool burnInProgress = false;
  byte burnOnMinutes[BURN_TIMES_PER_HOUR];
  byte burnOnMinutesSize = sizeof(burnOnMinutes);

  void updateMaxBrightness(byte newValue)
  {
    if (maxBrightness == newValue)
    {
      return;
    }
    maxBrightness = newValue;
    resetBrightness();
  }

  void burnIndicators()
  {
    for (byte k = 0; k < BURN_LOOPS; k++)
    {
      for (byte d = 0; d < DIGITS_AMOUNT; d++)
      {
        for (byte i = 0; i < INDICATORS_AMOUNT; i++)
        {
          digits[i]--;
          if (digits[i] < 0)
          {
            digits[i] = 9;
          }
        }
        delay(BURN_LOOP_DELAY);
      }
    }
  }
};

Indicators indicators;

#endif
