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

void convertTimeToArray(int8_t hrs, int8_t mins, byte result[])
{
  result[0] = (byte)hrs / 10;
  result[1] = (byte)hrs % 10;
  result[2] = (byte)mins / 10;
  result[3] = (byte)mins % 10;
}

#endif
