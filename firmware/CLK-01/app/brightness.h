#ifndef brightness_h
#define brightness_h

#include "time.h"
#include "backlight.h"
#include "dot.h"

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
  int8_t hrs = time.getHours();
  boolean isNight = (hrs >= NIGHT_START && hrs <= 23) || (hrs >= 0 && hrs < NIGHT_END);
  if (isNight)
  {
    indicatorMaxBrightness = INDICATOR_BRIGHTNESS_NIGHT;
  }
  else
  {
    indicatorMaxBrightness = INDICATOR_BRIGHTNESS;
  }
  backlight.setNightMode(isNight);
  dot.setNightMode(isNight);
  resetIndicatorMaxBrightness();
#endif
}

#endif
