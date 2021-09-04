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
