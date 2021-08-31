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
  if (++FLIP_EFFECT >= FLIP_EFFECT_NUM)
  {
    FLIP_EFFECT = 0;
  }
  EEPROM.put(0, FLIP_EFFECT);
  flipTimer.setInterval(FLIP_SPEED[FLIP_EFFECT]);
  for (byte i = 0; i < 4; i++)
  {
    indiDimm[i] = indiMaxBright;
    anodeStates[i] = 1;
  }
  // показать эффект
  newTimeFlag = true;
  for (byte i = 0; i < 4; i++)
  {
    indiDigits[i] = FLIP_EFFECT;
  }
}

void switchBacklight()
{
  if (++BACKL_MODE >= 3)
  {
    BACKL_MODE = 0;
  }
  EEPROM.put(1, BACKL_MODE);
  if (BACKL_MODE == 1)
  {
    setPWM(PIN_BKLIGHT, backlMaxBright);
  }
  else if (BACKL_MODE == 2)
  {
    digitalWrite(PIN_BKLIGHT, 0);
  }
}

void toggleGlitches()
{
  GLITCH_ALLOWED = !GLITCH_ALLOWED;
  EEPROM.put(2, GLITCH_ALLOWED);
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
