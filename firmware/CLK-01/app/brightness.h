#ifndef brightness_h
#define brightness_h

#include "indicators.h"
#include "time.h"
#include "backlight.h"
#include "dot.h"

void updateBrightness()
{
#if (NIGHT_MODE == NIGHT_MODE_ENABLED)
  int8_t hrs = time.getHours();
  boolean isNight = (hrs >= NIGHT_START && hrs <= 23) || (hrs >= 0 && hrs < NIGHT_END);
  backlight.setNightMode(isNight);
  dot.setNightMode(isNight);
  indicators.setNightMode(isNight);
#endif
}

#endif
