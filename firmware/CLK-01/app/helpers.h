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

byte *convertTimeToArray(int8_t hrs, int8_t mins)
{
  byte arr[4];
  arr[0] = (byte)hrs / 10;
  arr[1] = (byte)hrs % 10;

  arr[2] = (byte)mins / 10;
  arr[3] = (byte)mins % 10;

  debug("convertTimeToArray arr[0] " + String(arr[0]));
  debug("convertTimeToArray arr[1] " + String(arr[1]));
  debug("convertTimeToArray arr[2] " + String(arr[2]));
  debug("convertTimeToArray arr[3] " + String(arr[3]));
  return arr;
}

#endif
