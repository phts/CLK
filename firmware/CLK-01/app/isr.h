#ifndef isr_h
#define isr_h

#include "indicators.h"

const byte DIGIT_TO_DECODER_VALUE[] = {3, 2, 7, 4, 1, 9, 8, 0, 5, 6};
const byte INDICATOR_PINS[] = {PIN_HRS_L, PIN_HRS_R, PIN_MINS_L, PIN_MINS_R};
volatile int8_t curInd;
volatile int8_t arr[4];

ISR(TIMER2_COMPA_vect)
{
  arr[curInd]++;
  if (arr[curInd] >= indicators.brightness[curInd])
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

    if (indicators.brightness[curInd] > 0)
    {
      byte tmp = DIGIT_TO_DECODER_VALUE[indicators.digits[curInd]];
      setPin(DECODER_PIN_3, bitRead(tmp, 0));
      setPin(DECODER_PIN_6, bitRead(tmp, 1));
      setPin(DECODER_PIN_7, bitRead(tmp, 2));
      setPin(DECODER_PIN_4, bitRead(tmp, 3));
      setPin(INDICATOR_PINS[curInd], indicators.isOn(curInd));
    }
  }
}

#endif
