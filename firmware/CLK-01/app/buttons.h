#ifndef buttons_h
#define buttons_h

int8_t changeHrs, changeMins;
boolean modeAdjustLampState = false;

void settingsTick()
{
  if (mode == MODE_ADJUST)
  {
    if (!modeAdjustBlinkTimer.isReady())
    {
      return;
    }
    showTime(changeHrs, changeMins);
    modeAdjustLampState = !modeAdjustLampState;
    if (modeAdjustLampState)
    {
      turnOnAllLamps();
    }
    else
    {
      turnOffAllLamps();
    }
  }
}

void incHours()
{
  changeHrs++;
  if (changeHrs > 23)
  {
    changeHrs = 0;
  }
  showTime(changeHrs, changeMins);
}

void incMinutes()
{
  changeMins++;
  if (changeMins > 59)
  {
    changeMins = 0;
  }
  showTime(changeHrs, changeMins);
}

void switchEffects()
{
  if (++currentEffectsMode >= EFFECT_AMOUNT)
  {
    currentEffectsMode = 0;
  }
  EEPROM.put(MEMORY_CELL_EFFECTS, currentEffectsMode);
  flipTimer.setInterval(EFFECTS_SPEED[currentEffectsMode]);
  resetIndicatorMaxBrightness();
  turnOnAllLamps();

  timeJustChanged = true;
  for (byte i = 0; i < 4; i++)
  {
    indicatorDigits[i] = currentEffectsMode;
  }
}

void switchBacklight()
{
  if (++currentBklightMode >= BKLIGHT_AMOUNT)
  {
    currentBklightMode = 0;
  }
  EEPROM.put(MEMORY_CELL_BKLIGHT, currentBklightMode);
  resetBklightBrightness();
}

void toggleGlitches()
{
  currentGlitchesMode = !currentGlitchesMode;
  EEPROM.put(MEMORY_CELL_GLITCHES, currentGlitchesMode);
}

void startAdjust()
{
  turnOnAllLamps();
  changeHrs = hrs;
  changeMins = mins;
}

void finishAdjust()
{
  hrs = changeHrs;
  mins = changeMins;
  secs = 0;
  rtc.adjust(DateTime(2019, 12, 5, hrs, mins, 0));
  updateBrightness();
}

void buttonsTick()
{
  btnMode.tick();
  btnEffects.tick();
  btnBklight.tick();

  if (btnMode.isHold())
  {
    if (mode != MODE_ADJUST)
    {
      startAdjust();
    }
    mode = MODE_ADJUST;
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
    if (mode != MODE_CLOCK)
    {
      finishAdjust();
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
