#ifndef dot_h
#define dot_h

byte dotSmoothStep;
boolean isDotReady, dotUpDirection;
int dotBrightness;
boolean isDotTurnedOn;

void resetDot()
{
  isDotReady = true;
  dotUpDirection = true;
  dotBrightness = 0;
}

void resetDotBrightness()
{
  dotSmoothStep = ceil((float)dotMaxBrightness * 2 / DOT_TIMER * DOT_BRIGHTNESS_TIMER);
  if (dotSmoothStep == 0)
  {
    dotSmoothStep = 1;
  }
}

void dotBrightnessTick()
{
  if (!dotBrightnessTimer.isReady())
  {
    return;
  }
  if (dotUpDirection)
  {
    dotBrightness += dotSmoothStep;
    if (dotBrightness >= dotMaxBrightness)
    {
      dotUpDirection = false;
      dotBrightness = dotMaxBrightness;
    }
  }
  else
  {
    dotBrightness -= dotSmoothStep;
    if (dotBrightness <= 0)
    {
      isDotReady = false;
      dotBrightness = 0;
    }
  }
  setPWM(PIN_DOT, getPWM_CRT(dotBrightness));
}

void dotTick()
{
  if (DOT_MODE == DOT_MODE_SMOOTH && isDotReady)
  {
    dotBrightnessTick();
  }
  if (!dotTimer.isReady())
  {
    return;
  }
  if (DOT_MODE == DOT_MODE_SIMPLE)
  {
    dotBrightness = dotBrightness == 0 ? dotMaxBrightness : 0;
    setPWM(PIN_DOT, getPWM_CRT(dotBrightness));
    return;
  }

  if (DOT_MODE == DOT_MODE_SMOOTH)
  {
    resetDot();
    return;
  }
}

#endif
