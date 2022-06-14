#ifndef buttons_h
#define buttons_h

#include <EncButton.h>
#include "indicators.h"
#include "memory.h"
#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "glitches.h"
#include "nightMode.h"
#include "dot.h"

#define MODE_CLOCK 0
#define MODE_SET 1

class Control
{
public:
  Control() : blinkTimer(MODE_SET_BLINK_INTERVAL)
  {
    mode = MODE_CLOCK;
  }

  void setup()
  {
    btnEffects.setStepTimeout(MODE_SET_HOURS_INTERVAL);
    btnBklight.setStepTimeout(MODE_SET_MINS_INTERVAL);
    swMode.setHoldTimeout(0);
  }

  byte isClockMode()
  {
    return mode == MODE_CLOCK;
  }

  void tick()
  {
    swMode.tick();
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

    if (swMode.hold())
    {
      if (mode != MODE_SET)
      {
        startSet();
        mode = MODE_SET;
      }
      if (btnEffects.press() || btnEffects.step())
      {
        incHours();
      }
      else if (btnBklight.press() || btnBklight.step())
      {
        incMinutes();
      }
    }
    else
    {
      if (mode == MODE_SET)
      {
        finishSet();
        mode = MODE_CLOCK;
      }
      if (btnEffects.click())
      {
        switchEffects();
        debug(F("Switch effect"), effects.getMode());
      }
      else if (btnBklight.click())
      {
        switchBacklight();
        debug(F("Switch backlight"), backlight.getMode());
      }
      else if (btnEffects.held())
      {
        toggleGlitches();
        debug(F("Toggle glitches"), glitches.getMode());
      }
      else if (btnBklight.held())
      {
        toggleNightMode();
        debug(F("Toggle night mode"), nightMode.isEnabled());
      }
    }
    btnEffects.resetState();
    btnBklight.resetState();
  }

private:
  byte mode;
  timerMinim blinkTimer;
  EncButton<EB_TICK, PIN_SW_MODE> swMode;
  EncButton<EB_TICK, PIN_BTN_BKLIGHT> btnBklight;
  EncButton<EB_TICK, PIN_BTN_EFFECTS> btnEffects;
  int8_t changeHrs, changeMins;
  bool modeSetLampState = false;
  bool isEffectsDemoRunning = false;
  byte cachedTimeArray[INDICATORS_AMOUNT] = {0, 0, 0, 0};

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
    for (byte i = 0; i < INDICATORS_AMOUNT; i++)
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
    glitches.forceShow();
    memory.storeGlitches(glitches.getMode());
  }

  void toggleNightMode()
  {
    nightMode.toggle();
    memory.storeNightMode(nightMode.isEnabled());
  }

  void startSet()
  {
    btnBklight.setHoldTimeout(MODE_SET_MINS_HOLD_TIME);
    btnEffects.setHoldTimeout(MODE_SET_HOURS_HOLD_TIME);
    blinkTimer.reset();
    indicators.turnAllOff();
    changeHrs = time.getHours();
    changeMins = time.getMinutes();
    modeSetLampState = false;
    dot.turnOff();
  }

  void finishSet()
  {
    btnBklight.setHoldTimeout(500);
    btnEffects.setHoldTimeout(500);
    time.setTime(changeHrs, changeMins);
    indicators.turnAllOn();
    nightMode.apply(changeHrs);
    dot.turnOn();
  }
};

Control control;

#endif
