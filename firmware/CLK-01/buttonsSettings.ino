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
        anodeStates[0] = 1;
        anodeStates[1] = 1;
        anodeStates[2] = 1;
        anodeStates[3] = 1;
      }
      else
      {
        anodeStates[0] = 0;
        anodeStates[1] = 0;
        anodeStates[2] = 0;
        anodeStates[3] = 0;
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
  for (byte i = 0; i < 4; i++)
  {
    indicatorBrightness[i] = indicatorMaxBrightness;
    anodeStates[i] = 1;
  }

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
  anodeStates[0] = 1;
  anodeStates[1] = 1;
  anodeStates[2] = 1;
  anodeStates[3] = 1;
  changeHrs = hrs;
  changeMins = mins;
}

void finishAdjust()
{
  hrs = changeHrs;
  mins = changeMins;
  secs = 0;
  rtc.adjust(DateTime(2019, 12, 5, hrs, mins, 0));
  changeBright();
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
    if (btnEffects.isClick())
    {
      incHours();
    }
    else if (btnBklight.isClick())
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
    if (btnEffects.isClick())
    {
      switchEffects();
    }
    if (btnBklight.isClick())
    {
      switchBacklight();
    }
  }
}
