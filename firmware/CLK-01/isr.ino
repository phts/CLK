// динамическая индикация в прерывании таймера 2
ISR(TIMER2_COMPA_vect)
{
  indiCounter[curIndi]++; // счётчик индикатора
  if (indiCounter[curIndi] >= indiDimm[curIndi])
  {                           // если достигли порога диммирования
    setPin(opts[curIndi], 0); // выключить текущий индикатор
  }

  if (indiCounter[curIndi] > 25)
  {                           // достигли порога в 25 единиц
    indiCounter[curIndi] = 0; // сброс счетчика лампы
    if (++curIndi >= 4)
    {
      curIndi = 0; // смена лампы закольцованная
    }

    // отправить цифру из массива indiDigits согласно типу лампы
    if (indiDimm[curIndi] > 0)
    {
      byte thisDig = digitMask[indiDigits[curIndi]];
      setPin(PIN_DECODER_3, bitRead(thisDig, 0));
      setPin(PIN_DECODER_1, bitRead(thisDig, 1));
      setPin(PIN_DECODER_0, bitRead(thisDig, 2));
      setPin(PIN_DECODER_2, bitRead(thisDig, 3));
      setPin(opts[curIndi], anodeStates[curIndi]); // включить анод на текущую лампу
    }
  }
}
