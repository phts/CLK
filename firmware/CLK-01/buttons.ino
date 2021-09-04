int8_t changeHrs, changeMins;
boolean modeAdjustLampState = false;

void settingsTick()
{
  if (mode == MODE_ADJUST)
  {
    if (modeAdjustBlinkTimer.isReady())
    {
      sendTime(changeHrs, changeMins);
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
}

void incHours()
{
  changeHrs++;
  if (changeHrs > 23)
  {
    changeHrs = 0;
  }
  sendTime(changeHrs, changeMins);
}

void incMinutes()
{
  changeMins++;
  if (changeMins > 23)
  {
    changeMins = 0;
  }
  sendTime(changeHrs, changeMins);
}

void switchEffects()
{
  if (++currentEffectsMode >= EFFECTS_SPEEDS_AMOUNT)
  {
    currentEffectsMode = 0;
  }
  EEPROM.put(MEMORY_CELL_EFFECTS, currentEffectsMode);
  flipTimer.setInterval(EFFECTS_SPEED[currentEffectsMode]);
  resetInticatorsMaxBrightness();
  turnOnAllLamps();

  timeJustChanged = true;
  for (byte i = 0; i < 4; i++)
  {
    indicatorDigits[i] = currentEffectsMode;
  }
}

void switchBacklight()
{
  if (++currentBklightMode >= 3)
  {
    currentBklightMode = 0;
  }
  EEPROM.put(MEMORY_CELL_BKLIGHT, currentBklightMode);
  if (currentBklightMode == 1)
  {
    setPWM(PIN_BKLIGHT, bklightMaxBrightness);
  }
  else if (currentBklightMode == 2)
  {
    digitalWrite(PIN_BKLIGHT, 0);
  }
}

void toggleGlitches()
{
  currentGlitchesState = !currentGlitchesState;
  EEPROM.put(MEMORY_CELL_GLITCHES, currentGlitchesState);
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
