#ifndef helpers_h
#define helpers_h

void turnOnAllLamps()
{
  for (byte i = 0; i < 4; i++)
  {
    anodeStates[i] = 1;
  }
}

void turnOffAllLamps()
{
  for (byte i = 0; i < 4; i++)
  {
    anodeStates[i] = 0;
  }
}

void showTime(byte hours, byte minutes)
{
  indicatorDigits[0] = (byte)hours / 10;
  indicatorDigits[1] = (byte)hours % 10;
  indicatorDigits[2] = (byte)minutes / 10;
  indicatorDigits[3] = (byte)minutes % 10;
}

#endif
