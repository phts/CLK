byte dotBrightStep;
boolean dotBrightFlag, dotBrightDirection;
int dotBrightCounter;

void dotBrightnessTick()
{
  if (!(dotBrightFlag && dotBrightnessTimer.isReady()))
  {
    return;
  }
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

void resetDot()
{
  dotBrightFlag = true;
  dotBrightDirection = true;
  dotBrightCounter = 0;
}

void resetDotBrightness()
{
  dotBrightStep = ceil((float)dotMaxBrightness * 2 / DOT_INTERVAL * DOT_BRIGHTNESS_TIMER);
  if (dotBrightStep == 0)
  {
    dotBrightStep = 1;
  }
}
