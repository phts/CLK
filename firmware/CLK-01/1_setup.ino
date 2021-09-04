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

void setupRtc()
{
  rtc.begin();
  if (rtc.lostPower())
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  DateTime now = rtc.now();
  secs = now.second();
  mins = now.minute();
  hrs = now.hour();
}

void setupMemory()
{
  if (EEPROM.read(MEMORY_CELL_FIRST_RUN) != MEMORY_FLAG_FIRST_RUN)
  {
    EEPROM.put(MEMORY_CELL_FIRST_RUN, MEMORY_FLAG_FIRST_RUN);
    EEPROM.put(MEMORY_CELL_EFFECTS, currentEffectsMode);
    EEPROM.put(MEMORY_CELL_BKLIGHT, currentBklightMode);
    EEPROM.put(MEMORY_CELL_GLITCHES, currentGlitchesState);
  }
  EEPROM.get(MEMORY_CELL_EFFECTS, currentEffectsMode);
  EEPROM.get(MEMORY_CELL_BKLIGHT, currentBklightMode);
  EEPROM.get(MEMORY_CELL_GLITCHES, currentGlitchesState);
}

void setupBrightness()
{
  resetInticatorsMaxBrightness();
  resetDotBrightness();
  updateBrightness();
}

void setupTimers()
{
  resetBklightBrightnessTimer();
  glitchTimer.setInterval(random(GLITCH_MIN_INTERVAL * 1000L, GLITCH_MAX_INTERVAL * 1000L));
  flipTimer.setInterval(EFFECTS_SPEED[currentEffectsMode]);
}

void setup()
{
  randomSeed(analogRead(6) + analogRead(7));

  pinMode(PIN_DECODER_0, OUTPUT);
  pinMode(PIN_DECODER_1, OUTPUT);
  pinMode(PIN_DECODER_2, OUTPUT);
  pinMode(PIN_DECODER_3, OUTPUT);
  pinMode(PIN_HRS_L, OUTPUT);
  pinMode(PIN_HRS_R, OUTPUT);
  pinMode(PIN_MINS_L, OUTPUT);
  pinMode(PIN_MINS_R, OUTPUT);
  pinMode(PIN_GEN, OUTPUT);
  pinMode(PIN_DOT, OUTPUT);
  pinMode(PIN_BKLIGHT, OUTPUT);

  setupPwm();
  setupRtc();
  setupMemory();

  sendTime(hrs, mins);
  setupBrightness();
  setupTimers();

  btnEffects.setStepTimeout(ADJ_TIME_HOURS_INTERVAL);
  btnEffects.setTimeout(ADJ_TIME_HOURS_TIMEOUT);
  btnBklight.setStepTimeout(ADJ_TIME_MINS_INTERVAL);
  btnBklight.setTimeout(ADJ_TIME_MINS_TIMEOUT);
}
