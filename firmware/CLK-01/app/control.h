#ifndef buttons_h
#define buttons_h

#include <GyverButton.h>
#include "indicators.h"
#include "memory.h"
#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "glitches.h"
#include "nightMode.h"

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
      isEffectsDemoRunning = effects.tick(time.getHours(), time.getMinutes(), cachedTimeArray);
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
  byte cachedTimeArray[4] = {0, 0, 0, 0};

  void settingsTick()
  {
    if (!blinkTimer.isReady())
    {
      return;
    }
    indicators.showTime(changeHrs, changeMins);
    modeSetLampState = !modeSetLampState;
    modeSetLampState ? indicators.turnAllOn() : indicators.turnAllOff();
  }

  void incHours()
  {
    changeHrs++;
    if (changeHrs > 23)
    {
      changeHrs = 0;
    }
    blinkTimer.reset();
    indicators.turnAllOn();
    indicators.showTime(changeHrs, changeMins);
  }

  void incMinutes()
  {
    changeMins++;
    if (changeMins > 59)
    {
      changeMins = 0;
    }
    blinkTimer.reset();
    indicators.turnAllOn();
    indicators.showTime(changeHrs, changeMins);
  }

  void switchEffects()
  {
    effects.toggle();
    memory.storeEffects(effects.getMode());
    indicators.resetBrightness();
    indicators.turnAllOn();
    isEffectsDemoRunning = true;
    for (byte i = 0; i < 4; i++)
    {
      indicators.digits[i] = effects.getMode();
    }
    convertTimeToArray(time.getHours(), time.getMinutes(), cachedTimeArray);
  }

  void switchBacklight()
  {
    backlight.toggle();
    memory.storeBacklight(backlight.getMode());
  }

  void toggleGlitches()
  {
    glitches.toggle();
    memory.storeGlitches(glitches.getMode());
  }

  void startSet()
  {
    blinkTimer.reset();
    indicators.turnAllOff();
    changeHrs = time.getHours();
    changeMins = time.getMinutes();
    modeSetLampState = false;
  }

  void finishSet()
  {
    time.setTime(changeHrs, changeMins);
    indicators.turnAllOn();
    nightMode.setup(changeHrs);
  }
};

Control control;

#endif
