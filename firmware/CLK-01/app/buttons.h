#ifndef buttons_h
#define buttons_h

#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "glitches.h"

int8_t changeHrs, changeMins;
boolean modeSetLampState = false;
boolean isEffectsDemoRunning = false;

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
  isEffectsDemoRunning = true;
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
  changeHrs = time.getHours();
  changeMins = time.getMinutes();
}

void finishSet()
{
  time.setTime(changeHrs, changeMins);
  turnOnAllLamps();
  updateBrightness();
}

void buttonsTick()
{
  btnMode.tick();
  btnEffects.tick();
  btnBklight.tick();

  if (isEffectsDemoRunning)
  {
    byte demoTime = effects.getMode() * 10 + effects.getMode();
    isEffectsDemoRunning = effects.tick(demoTime, demoTime, convertTimeToArray(demoTime, demoTime));
  }

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
