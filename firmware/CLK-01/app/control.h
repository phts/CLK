#ifndef buttons_h
#define buttons_h

#include <EEPROM.h>
#include <GyverButton.h>
#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "glitches.h"

#define MODE_CLOCK 0
#define MODE_SET 1

class Control
{
public:
  Control() : blinkTimer(MODE_SET_BLINK_INTERVAL),
              btnMode(PIN_BTN_MODE, HIGH_PULL, NORM_OPEN),
              btnBklight(PIN_BTN_BKLIGHT, HIGH_PULL, NORM_OPEN),
              btnEffects(PIN_BTN_EFFECTS, HIGH_PULL, NORM_OPEN)
  {
    mode = MODE_CLOCK;
  }

  void setup()
  {
    btnEffects.setStepTimeout(MODE_SET_HOURS_INTERVAL);
    btnEffects.setTimeout(MODE_SET_HOURS_HOLD_TIME);
    btnBklight.setStepTimeout(MODE_SET_MINS_INTERVAL);
    btnBklight.setTimeout(MODE_SET_MINS_HOLD_TIME);
  }

  byte isClockMode()
  {
    return mode == MODE_CLOCK;
  }

  void tick()
  {
    btnMode.tick();
    btnEffects.tick();
    btnBklight.tick();

    if (mode == MODE_SET)
    {
      settingsTick();
    }

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

private:
  byte mode;
  timerMinim blinkTimer;
  GButton btnMode;
  GButton btnBklight;
  GButton btnEffects;
  int8_t changeHrs, changeMins;
  boolean modeSetLampState = false;
  boolean isEffectsDemoRunning = false;

  void settingsTick()
  {
    if (!blinkTimer.isReady())
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
    blinkTimer.reset();
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
    blinkTimer.reset();
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
};

Control control;

#endif
