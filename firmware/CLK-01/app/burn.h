#ifndef burn_h
#define burn_h

byte oldHrs = -1;
bool burnInProgress = false;
byte burnOnMinutes[BURN_TIMES_PER_HOUR];
byte burnOnMinutesSize = sizeof(burnOnMinutes);

void burnIndicators()
{
  for (byte k = 0; k < BURN_LOOPS; k++)
  {
    for (byte d = 0; d < 10; d++)
    {
      for (byte i = 0; i < 4; i++)
      {
        indicatorDigits[i]--;
        if (indicatorDigits[i] < 0)
        {
          indicatorDigits[i] = 9;
        }
      }
      delay(BURN_LOOP_DELAY);
    }
  }
}

void burnTick()
{
  if (burnInProgress)
  {
    return;
  }
  if (oldHrs != hrs)
  {
    oldHrs = hrs;
    debug("New hour! Burn on minutes:");
    for (byte i = 0; i < burnOnMinutesSize; i++)
    {
      burnOnMinutes[i] = random(60 / burnOnMinutesSize * i + 5, 60 / burnOnMinutesSize * (i + 1) - 5 + 1);
      debug(String(burnOnMinutes[i]));
    }
  }
  if (mode != MODE_CLOCK)
  {
    return;
  }
  for (byte i = 0; i < burnOnMinutesSize; i++)
  {
    if (mins == burnOnMinutes[i] && secs >= 15 && secs <= 45)
    {
      burnInProgress = true;
      burnOnMinutes[i] = -1;
      burnIndicators();
      burnInProgress = false;
      break;
    }
  }
}

#endif
