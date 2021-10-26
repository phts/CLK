#ifndef helpers_h
#define helpers_h

void convertTimeToArray(int8_t hrs, int8_t mins, byte result[])
{
  result[0] = (byte)hrs / 10;
  result[1] = (byte)hrs % 10;
  result[2] = (byte)mins / 10;
  result[3] = (byte)mins % 10;
}

const uint8_t CRTgamma[256] PROGMEM = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 12, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 22, 22, 23, 23, 24, 25, 25, 26, 26, 27, 28, 28, 29, 30, 30, 31, 32, 33, 33, 34, 35, 35, 36, 37, 38, 39, 39, 40, 41, 42, 43, 43, 44, 45, 46, 47, 48, 49, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 79, 80, 81, 82, 83, 84, 85, 87, 88, 89, 90, 91, 93, 94, 95, 96, 98, 99, 100, 101, 103, 104, 105, 107, 108, 109, 110, 112, 113, 115, 116, 117, 119, 120, 121, 123, 124, 126, 127, 129, 130, 131, 133, 134, 136, 137, 139, 140, 142, 143, 145, 146, 148, 149, 151, 153, 154, 156, 157, 159, 161, 162, 164, 165, 167, 169, 170, 172, 174, 175, 177, 179, 180, 182, 184, 186, 187, 189, 191, 193, 194, 196, 198, 200, 202, 203, 205, 207, 209, 211, 213, 214, 216, 218, 220, 222, 224, 226, 228, 230, 232, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255};

byte getPWM_CRT(byte val)
{
  return pgm_read_byte(&(CRTgamma[val]));
}

// быстрый digitalWrite
void setPin(uint8_t pin, uint8_t x)
{
  switch (pin)
  {       // откл pwm
  case 3: // 2B
    bitClear(TCCR2A, COM2B1);
    break;
  case 5: // 0B
    bitClear(TCCR0A, COM0B1);
    break;
  case 6: // 0A
    bitClear(TCCR0A, COM0A1);
    break;
  case 9: // 1A
    bitClear(TCCR1A, COM1A1);
    break;
  case 10: // 1B
    bitClear(TCCR1A, COM1B1);
    break;
  case 11: // 2A
    bitClear(TCCR2A, COM2A1);
    break;
  }

  if (pin < 8)
    bitWrite(PORTD, pin, x);
  else if (pin < 14)
    bitWrite(PORTB, (pin - 8), x);
  else if (pin < 20)
    bitWrite(PORTC, (pin - 14), x);
  else
    return;
}

// быстрый analogWrite
void setPWM(uint8_t pin, uint16_t duty)
{
  if (duty == 0)
  {
    setPin(pin, LOW);
  }
  else
  {
    switch (pin)
    {
    case PIN_DOT:
      bitSet(TCCR1A, COM1B1);
      OCR1B = duty;
      break;
    case PIN_GEN:
      bitSet(TCCR1A, COM1A1);
      OCR1A = duty;
      break;
    case PIN_BKLIGHT:
      bitSet(TCCR2A, COM2A1);
      OCR2A = duty;
      break;
    default:
      break;
    }
  }
}

#endif
