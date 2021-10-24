#ifndef setup_h
#define setup_h

#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "dot.h"
#include "glitches.h"

void setupPwm()
{
  // задаем частоту ШИМ на 9 и 10 выводах 31 кГц
  TCCR1B = (TCCR1B & 0b11111000) | 1; // ставим делитель 1

  // включаем ШИМ
  setPWM(PIN_GEN, DUTY_CYCLE);

  // перенастраиваем частоту ШИМ на пинах 3 и 11 на 7.8 кГц и разрешаем прерывания COMPA
  TCCR2B = (TCCR2B & B11111000) | 2; // делитель 8
  TCCR2A |= (1 << WGM21);            // включить CTC режим для COMPA
  TIMSK2 |= (1 << OCIE2A);           // включить прерывания по совпадению COMPA
}

void setupMemory()
{
  if (MEMORY != MEMORY_ENABLED)
  {
    return;
  }
  if (EEPROM.read(MEMORY_CELL_FIRST_RUN) != MEMORY_FLAG_FIRST_RUN)
  {
    EEPROM.put(MEMORY_CELL_FIRST_RUN, MEMORY_FLAG_FIRST_RUN);
    EEPROM.put(MEMORY_CELL_EFFECTS, effects.getMode());
    EEPROM.put(MEMORY_CELL_BKLIGHT, backlight.getMode());
    EEPROM.put(MEMORY_CELL_GLITCHES, glitches.getMode());
  }
  byte newEffectMode, newBklightMode, newGlitchesMode;
  EEPROM.get(MEMORY_CELL_EFFECTS, newEffectMode);
  EEPROM.get(MEMORY_CELL_BKLIGHT, newBklightMode);
  EEPROM.get(MEMORY_CELL_GLITCHES, newGlitchesMode);
  effects.setMode(newEffectMode);
  backlight.setMode(newBklightMode);
  glitches.setMode(newGlitchesMode);
}

void setupBrightness()
{
  resetIndicatorMaxBrightness();
  updateBrightness();
}

void setup()
{
  setupDebug();
  randomSeed(analogRead(6) + analogRead(7));

  pinMode(DECODER_PIN_7, OUTPUT);
  pinMode(DECODER_PIN_6, OUTPUT);
  pinMode(DECODER_PIN_4, OUTPUT);
  pinMode(DECODER_PIN_3, OUTPUT);
  pinMode(PIN_HRS_L, OUTPUT);
  pinMode(PIN_HRS_R, OUTPUT);
  pinMode(PIN_MINS_L, OUTPUT);
  pinMode(PIN_MINS_R, OUTPUT);
  pinMode(PIN_GEN, OUTPUT);
  pinMode(PIN_DOT, OUTPUT);
  pinMode(PIN_BKLIGHT, OUTPUT);

  setupPwm();
  time.setup();
  setupMemory();

  showTime(time.getHours(), time.getMinutes());
  setupBrightness();
  dot.setup();
  effects.setup();
  backlight.setup();
  glitches.setup();

  btnEffects.setStepTimeout(MODE_SET_HOURS_INTERVAL);
  btnEffects.setTimeout(MODE_SET_HOURS_HOLD_TIME);
  btnBklight.setStepTimeout(MODE_SET_MINS_INTERVAL);
  btnBklight.setTimeout(MODE_SET_MINS_HOLD_TIME);
}

#endif
