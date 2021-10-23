#ifndef brightness_h
#define brightness_h

void resetIndicatorMaxBrightness()
{
  for (byte i = 0; i < 4; i++)
  {
    indicatorBrightness[i] = indicatorMaxBrightness;
  }
}

void updateBrightness()
{
#if (NIGHT_MODE == NIGHT_MODE_ENABLED)
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
  resetIndicatorMaxBrightness();
  resetDotBrightness();
  resetBklightBrightness();
#endif
}

#endif
