boolean backlBrightFlag, backlBrightDirection;
int backlBrightCounter;

void bklightBrightnessTick()
{
  if (currentBklightMode == 0 && bklightBrightnessTimer.isReady())
  {
    if (bklightMaxBrightness > 0)
    {
      if (backlBrightDirection)
      {
        if (!backlBrightFlag)
        {
          backlBrightFlag = true;
          bklightBrightnessTimer.setInterval((float)BKLIGHT_STEPS / bklightMaxBrightness / 2 * BKLIGHT_PERIOD);
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
}

void dotBrightnessTick()
{
  if (dotBrightFlag && dotBrightnessTimer.isReady())
  {
    if (dotBrightDirection)
    {
      dotBrightCounter += dotBrightStep;
      if (dotBrightCounter >= dotMaxBrightness)
      {
        dotBrightDirection = false;
        dotBrightCounter = dotMaxBrightness;
      }
    }
    else
    {
      dotBrightCounter -= dotBrightStep;
      if (dotBrightCounter <= 0)
      {
        dotBrightDirection = true;
        dotBrightFlag = false;
        dotBrightCounter = 0;
      }
    }
    setPWM(PIN_DOT, getPWM_CRT(dotBrightCounter));
  }
}

void updateBrightness()
{
#if (NIGHT_LIGHT == 1)
  if ((hrs >= NIGHT_START && hrs <= 23) || (hrs >= 0 && hrs < NIGHT_END))
  {
    indicatorMaxBrightness = INDICATOR_BRIGHTNESS_NIGHT;
    dotMaxBrightness = DOT_BRIGHTNESS_NIGHT;
    bklightMaxBrightness = BKLIGHT_BRIGHTNESS_NIGHT;
  }
  else
  {
    indicatorMaxBrightness = INDICATOR_BRIGHTNESS;
    dotMaxBrightness = DOT_BRIGHTNESS;
    bklightMaxBrightness = BKLIGHT_BRIGHTNESS;
  }
  for (byte i = 0; i < 4; i++)
  {
    indicatorBrightness[i] = indicatorMaxBrightness;
  }

  dotBrightStep = ceil((float)dotMaxBrightness * 2 / DOT_INTERVAL * DOT_BRIGHTNESS_TIMER);
  if (dotBrightStep == 0)
  {
    dotBrightStep = 1;
  }

  if (bklightMaxBrightness > 0)
  {
    bklightBrightnessTimer.setInterval((float)BKLIGHT_STEPS / bklightMaxBrightness / 2 * BKLIGHT_PERIOD);
  }
  indiBrightCounter = indicatorMaxBrightness;

  //change PWM to apply bklightMaxBrightness in case of maximum bright mode
  if (currentBklightMode == 1)
  {
    setPWM(PIN_BKLIGHT, bklightMaxBrightness);
  }
#endif
}
