#ifndef buttons_h
#define buttons_h

#include "effects.h"
#include "backlight.h"
#include "glitches.h"

int8_t changeHrs, changeMins;
boolean modeSetLampState = false;

void settingsTick()
{
  if (mode != MODE_SET)
  {
    return;
  }
  if (!modeSetBlinkTimer.isReady())
  {
    return;
  }
  showTime(changeHrs, changeMins);
  modeSetLampState = !modeSetLampState;
  if (modeSetLampState)
  {
    turnOnAllLamps();
  }
  else
  {
    turnOffAllLamps();
  }
}

void incHours()
{
  changeHrs++;
  if (changeHrs > 23)
  {
    changeHrs = 0;
  }
  modeSetBlinkTimer.reset();
  turnOnAllLamps();
  showTime(changeHrs, changeMins);
}

void incMinutes()
{
  changeMins++;
  if (changeMins > 59)
  {
    changeMins = 0;
  }
  modeSetBlinkTimer.reset();
  turnOnAllLamps();
  showTime(changeHrs, changeMins);
}

void switchEffects()
{
  effects.toggle();
  EEPROM.put(MEMORY_CELL_EFFECTS, effects.getMode());
  resetIndicatorMaxBrightness();
  turnOnAllLamps();

  timeJustChanged = true;
  for (byte i = 0; i < 4; i++)
  {
    indicatorDigits[i] = effects.getMode();
  }
}

void switchBacklight()
{
  backlight.toggle();
  EEPROM.put(MEMORY_CELL_BKLIGHT, backlight.getMode());
}

void toggleGlitches()
{
  glitches.toggle();
  EEPROM.put(MEMORY_CELL_GLITCHES, glitches.getMode());
}

void startSet()
{
  turnOnAllLamps();
  changeHrs = hrs;
  changeMins = mins;
}

void finishSet()
{
  hrs = changeHrs;
  mins = changeMins;
  secs = 0;
  rtc.adjust(DateTime(2019, 12, 5, hrs, mins, 0));
  turnOnAllLamps();
  updateBrightness();
}

void buttonsTick()
{
  btnMode.tick();
  btnEffects.tick();
  btnBklight.tick();

  if (btnMode.isHold())
  {
    if (mode != MODE_SET)
    {
      startSet();
    }
    mode = MODE_SET;
    if (btnEffects.isPress() || btnEffects.isStep())
    {
      incHours();
    }
    else if (btnBklight.isPress() || btnBklight.isStep())
    {
      incMinutes();
    }
  }
  else
  {
    if (mode == MODE_SET)
    {
      finishSet();
    }
    mode = MODE_CLOCK;
    if (btnEffects.isPress())
    {
      switchEffects();
    }
    if (btnBklight.isPress())
    {
      switchBacklight();
    }
  }
}

#endif
