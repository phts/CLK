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
    case 5:
      bitSet(TCCR0A, COM0B1);
      OCR0B = duty;
      break;
    case 6:
      bitSet(TCCR0A, COM0A1);
      OCR0A = duty;
      break;
    case 10:
      bitSet(TCCR1A, COM1B1);
      OCR1B = duty;
      break;
    case 9:
      bitSet(TCCR1A, COM1A1);
      OCR1A = duty;
      break;
    case 3:
      bitSet(TCCR2A, COM2B1);
      OCR2B = duty;
      break;
    case 11:
      bitSet(TCCR2A, COM2A1);
      OCR2A = duty;
      break;
    default:
      break;
    }
  }
}
