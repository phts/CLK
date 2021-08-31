const byte INDICATOR_PINS[] = {PIN_HRS_L, PIN_HRS_R, PIN_MINS_L, PIN_MINS_R};
volatile int8_t curInd;
volatile int8_t arr[4];

ISR(TIMER2_COMPA_vect)
{
  arr[curInd]++;
  if (arr[curInd] >= indicatorBrightness[curInd])
  {
    setPin(INDICATOR_PINS[curInd], 0);
  }

  if (arr[curInd] > 25)
  {
    arr[curInd] = 0;
    if (++curInd >= 4)
    {
      curInd = 0;
    }

    if (indicatorBrightness[curInd] > 0)
    {
      byte thisDig = DIGIT_TO_DECODER_VALUE[indicatorDigits[curInd]];
      setPin(PIN_DECODER_3, bitRead(thisDig, 0));
      setPin(PIN_DECODER_1, bitRead(thisDig, 1));
      setPin(PIN_DECODER_0, bitRead(thisDig, 2));
      setPin(PIN_DECODER_2, bitRead(thisDig, 3));
      setPin(INDICATOR_PINS[curInd], anodeStates[curInd]);
    }
  }
}
