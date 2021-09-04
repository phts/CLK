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

  // задаем частоту ШИМ на 9 и 10 выводах 31 кГц
  TCCR1B = (TCCR1B & 0b11111000) | 1; // ставим делитель 1

  // включаем ШИМ
  setPWM(9, DUTY_CYCLE);

  // перенастраиваем частоту ШИМ на пинах 3 и 11 на 7.8 кГц и разрешаем прерывания COMPA
  TCCR2B = (TCCR2B & B11111000) | 2; // делитель 8
  TCCR2A |= (1 << WGM21);            // включить CTC режим для COMPA
  TIMSK2 |= (1 << OCIE2A);           // включить прерывания по совпадению COMPA

  // ---------- RTC -----------
  rtc.begin();
  if (rtc.lostPower())
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  DateTime now = rtc.now();
  secs = now.second();
  mins = now.minute();
  hrs = now.hour();

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

  sendTime(hrs, mins); // отправить время на индикаторы
  changeBright();      // изменить яркость согласно времени суток

  for (byte i = 0; i < 4; i++)
  {
    indicatorBrightness[i] = indicatorMaxBrightness;
  }

  // расчёт шага яркости точки
  dotBrightStep = ceil((float)dotMaxBrightness * 2 / DOT_INTERVAL * DOT_BRIGHTNESS_TIMER);
  if (dotBrightStep == 0)
  {
    dotBrightStep = 1;
  }

  // дыхание подсветки
  if (bklightMaxBrightness > 0)
  {
    backlBrightTimer.setInterval((float)BKLIGHT_STEPS / bklightMaxBrightness / 2 * BKLIGHT_PERIOD);
  }

  // стартовый период глюков
  glitchTimer.setInterval(random(GLITCH_MIN_INTERVAL * 1000L, GLITCH_MAX_INTERVAL * 1000L));
  indiBrightCounter = indicatorMaxBrightness;

  // скорость режима при запуске
  flipTimer.setInterval(EFFECTS_SPEED[currentEffectsMode]);

  btnEffects.setStepTimeout(ADJ_TIME_HOURS_INTERVAL);
  btnEffects.setTimeout(ADJ_TIME_HOURS_TIMEOUT);
  btnBklight.setStepTimeout(ADJ_TIME_MINS_INTERVAL);
  btnBklight.setTimeout(ADJ_TIME_MINS_TIMEOUT);
}
