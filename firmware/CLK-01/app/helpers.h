#ifndef helpers_h
#define helpers_h

void convertTimeToArray(int8_t hrs, int8_t mins, byte result[])
{
  result[0] = (byte)hrs / 10;
  result[1] = (byte)hrs % 10;
  result[2] = (byte)mins / 10;
  result[3] = (byte)mins % 10;
}

#endif
