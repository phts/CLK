#ifndef backlight_h
#define backlight_h

boolean backlBrightFlag, backlBrightDirection;
int backlBrightCounter;

void resetBklightBrightnessTimer()
{
  if (bklightMaxBrightness > 0)
  {
    bklightBrightnessTimer.setInterval((float)BKLIGHT_STEPS / bklightMaxBrightness / 2 * BKLIGHT_PERIOD);
  }
}

void resetBklightBrightness()
{
  if (currentBklightMode == BKLIGHT_ON)
  {
    setPWM(PIN_BKLIGHT, bklightMaxBrightness);
  }
  resetBklightBrightnessTimer();
}

void bklightBrightnessTick()
{
  if (currentBklightMode != BKLIGHT_FLASH)
  {
    return;
  }
  if (!bklightBrightnessTimer.isReady())
  {
    return;
  }
  if (bklightMaxBrightness > 0)
  {
    if (backlBrightDirection)
    {
      if (!backlBrightFlag)
      {
        backlBrightFlag = true;
        resetBklightBrightnessTimer();
      }
      backlBrightCounter += BKLIGHT_STEPS;
      if (backlBrightCounter >= bklightMaxBrightness)
      {
        backlBrightDirection = false;
        backlBrightCounter = bklightMaxBrightness;
      }
    }
    else
    {
      backlBrightCounter -= BKLIGHT_STEPS;
      if (backlBrightCounter <= BKLIGHT_MIN_BRIGHTNESS)
      {
        backlBrightDirection = true;
        backlBrightCounter = BKLIGHT_MIN_BRIGHTNESS;
        bklightBrightnessTimer.setInterval(BKLIGHT_DELAY);
        backlBrightFlag = false;
      }
    }
    setPWM(PIN_BKLIGHT, getPWM_CRT(backlBrightCounter));
  }
  else
  {
    digitalWrite(PIN_BKLIGHT, 0);
  }
}

#endif
