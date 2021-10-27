#ifndef setup_h
#define setup_h

#include <Wire.h>
#include "indicators.h"
#include "memory.h"
#include "time.h"
#include "effects.h"
#include "backlight.h"
#include "dot.h"
#include "glitches.h"
#include "control.h"
#include "nightMode.h"

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
  indicators.setup();
  indicators.showTime(time.getHours(), time.getMinutes());

  StoredData data = memory.setup(INITIAL_EFFECTS_MODE, INITIAL_BKLIGHT_MODE, INITIAL_GLITCHES_MODE, INITIAL_NIGHT_MODE);
  dot.setup();
  effects.setup(data.effectsMode);
  backlight.setup(data.bklightMode);
  glitches.setup(data.glitchesMode);
  nightMode.setup(data.nightmodeMode);
  control.setup();
}

#endif
