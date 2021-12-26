#ifndef indicators_h
#define indicators_h

#define INDICATOR_TURNED_OFF 0
#define INDICATOR_TURNED_ON 1

class Indicators
{
public:
  volatile int8_t brightness[INDICATORS_AMOUNT]; // 0--24
  volatile int8_t digits[INDICATORS_AMOUNT];     // 0--9

  Indicators(byte initialMaxBrightness)
  {
    indicatorMaxBrightness = initialMaxBrightness;
  }

  void setup()
  {
    resetBrightness();
  }

  void resetBrightness()
  {
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      brightness[i] = indicatorMaxBrightness;
    }
  }
  void setNightMode(boolean isNight)
  {
    indicatorMaxBrightness = isNight ? INDICATOR_BRIGHTNESS_NIGHT : INDICATOR_BRIGHTNESS;
    resetBrightness();
  }

  byte getMaxBrightness()
  {
    return indicatorMaxBrightness;
  }

  void showTime(byte hours, byte minutes)
  {
    convertTimeToArray(hours, minutes, digits);
  }

  boolean isOn(byte n)
  {
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

  void turnAllOn()
  {
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      anodeStates[i] = INDICATOR_TURNED_ON;
    }
  }

  void turnAllOff()
  {
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
    {
      anodeStates[i] = INDICATOR_TURNED_OFF;
    }
  }

  void burnTick(boolean isNewHour, byte mins, byte secs, boolean enabled)
  {
    if (burnInProgress)
    {
      return;
    }
    if (isNewHour)
    {
      for (byte i = 0; i < burnOnMinutesSize; i++)
      {
        burnOnMinutes[i] = random(60 / burnOnMinutesSize * i + 5, 60 / burnOnMinutesSize * (i + 1) - 5 + 1);
      }
    }
    if (!enabled)
    {
      return;
    }
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

private:
  byte indicatorMaxBrightness;
  boolean anodeStates[INDICATORS_AMOUNT] = {1, 1, 1, 1};
  bool burnInProgress = false;
  byte burnOnMinutes[BURN_TIMES_PER_HOUR];
  byte burnOnMinutesSize = sizeof(burnOnMinutes);

  void burnIndicators()
  {
    for (byte k = 0; k < BURN_LOOPS; k++)
    {
      for (byte d = 0; d < 10; d++)
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

Indicators indicators(INDICATOR_BRIGHTNESS);

#endif
