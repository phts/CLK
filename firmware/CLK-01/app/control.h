#ifndef buttons_h
#define buttons_h

#include <timer2Minim.h>
#include <EncButton.h>
#include "indicators.h"
#include "memory.h"
#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "glitches.h"
#include "nightMode.h"
#include "dot.h"
#include "power.h"
#include "confirmation.h"

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
    swStandby.setHoldTimeout(0);
  }

  byte isClockMode()
  {
    return mode == MODE_CLOCK;
  }

  bool isStandbyEnabled()
  {
    return standbyEnabled;
  }

  void tick()
  {
    swStandby.tick();
    swMode.tick();
    btnEffects.tick();
    btnBklight.tick();
    standbyEnabled = DEBUG_STANDBY_ENABLED || swStandby.hold();

    if (power.isOff())
    {
      if (!exitingStandby && (btnEffects.press() || btnBklight.press()))
      {
        exitingStandby = true;
        power.resetStandbyTimer();
        backlight.reset();
        return;
      }
    }
    if (exitingStandby)
    {
      if (btnEffects.click() || btnEffects.held() || btnBklight.click() || btnBklight.held())
      {
        exitingStandby = false;
        btnEffects.resetState();
        btnBklight.resetState();
      }
      return;
    }

    if (mode == MODE_SET)
    {
      settingsTick();
    }

    if (isEffectsDemoRunning)
    {
      isEffectsDemoRunning = effects.tick(time.getHours(), time.getMinutes(), cachedTimeArray);
    }
    if (confirmation.isRunning())
    {
      confirmation.tick(time.getHours(), time.getMinutes());
    }

    if (swMode.hold())
    {
      if (mode != MODE_SET)
      {
        startSet();
        mode = MODE_SET;
        power.resetStandbyTimer();
        debug(F("Switch to SET mode"));
      }
      if (btnEffects.press() || btnEffects.step())
      {
        incHours();
        power.resetStandbyTimer();
      }
      else if (btnBklight.press() || btnBklight.step())
      {
        incMinutes();
        power.resetStandbyTimer();
      }
    }
    else
    {
      if (mode == MODE_SET)
      {
        finishSet();
        mode = MODE_CLOCK;
        power.resetStandbyTimer();
        debug(F("Switch to CLOCK mode"));
      }
      if (btnEffects.click())
      {
        switchEffects();
        power.resetStandbyTimer();
        debug(F("Switch effect"), effects.getMode());
      }
      else if (btnBklight.click())
      {
        switchBacklight();
        power.resetStandbyTimer();
        debug(F("Switch backlight"), backlight.getMode());
      }
      else if (btnEffects.held())
      {
        toggleGlitches();
        power.resetStandbyTimer();
        debug(F("Toggle glitches"), glitches.getMode());
      }
      else if (btnBklight.held())
      {
        toggleNightMode();
        power.resetStandbyTimer();
        debug(F("Toggle night mode"), nightMode.getMode());
      }
    }
    btnEffects.resetState();
    btnBklight.resetState();
  }

private:
  byte mode;
  bool standbyEnabled;
  timerMinim blinkTimer;
  EncButton<EB_TICK, PIN_SW_MODE> swMode;
  EncButton<EB_TICK, PIN_BTN_BKLIGHT> btnBklight;
  EncButton<EB_TICK, PIN_BTN_EFFECTS> btnEffects;
  EncButton<EB_TICK, PIN_SW_STANDBY> swStandby;
  int8_t changeHrs, changeMins;
  bool modeSetLampState = false;
  bool isEffectsDemoRunning = false;
  byte cachedTimeArray[INDICATORS_AMOUNT] = {0, 0, 0, 0};
  bool exitingStandby = false;

  void settingsTick()
  {
    if (!blinkTimer.isReady())
    {
      return;
    }
    indicators.writeTime(changeHrs, changeMins);
    modeSetLampState = !modeSetLampState;
    modeSetLampState ? indicators.turnOnAll() : indicators.turnOffAll();
  }

  void incHours()
  {
    changeHrs++;
    if (changeHrs > 23)
    {
      changeHrs = 0;
    }
    blinkTimer.reset();
    indicators.turnOnAll();
    indicators.writeTime(changeHrs, changeMins);
  }

  void incMinutes()
  {
    changeMins++;
    if (changeMins > 59)
    {
      changeMins = 0;
    }
    blinkTimer.reset();
    indicators.turnOnAll();
    indicators.writeTime(changeHrs, changeMins);
  }

  void switchEffects()
  {
    effects.toggle();
    memory.storeEffects(effects.getMode());
    indicators.resetBrightness();
    indicators.turnOnAll();
    isEffectsDemoRunning = true;
    indicators.writeAll(effects.getMode());
    convertTimeToArray(time.getHours(), time.getMinutes(), cachedTimeArray);
  }

  void switchBacklight()
  {
    backlight.toggle();
    memory.storeBacklight(backlight.getMode());
    confirmation.show(CONFIRMATION_TYPE_BKLIGHT, backlight.getMode());
  }

  void toggleGlitches()
  {
    glitches.toggle();
    glitches.forceShow();
    memory.storeGlitches(glitches.getMode());
    confirmation.show(CONFIRMATION_TYPE_GLITCHES, glitches.getMode());
  }

  void toggleNightMode()
  {
    nightMode.toggle();
    memory.storeNightMode(nightMode.getMode());
    confirmation.show(CONFIRMATION_TYPE_NIGHTMODE, nightMode.getMode());
  }

  void startSet()
  {
    btnBklight.setHoldTimeout(MODE_SET_MINS_HOLD_TIME);
    btnEffects.setHoldTimeout(MODE_SET_HOURS_HOLD_TIME);
    blinkTimer.reset();
    indicators.turnOffAll();
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
    indicators.turnOnAll();
    nightMode.apply(changeHrs);
    dot.turnOn();
  }
};

Control control;

#endif
