void burnIndicators()
{
  for (byte k = 0; k < BURN_LOOPS; k++)
  {
    for (byte d = 0; d < 10; d++)
    {
      for (byte i = 0; i < 4; i++)
      {
        indicatorDigits[i]--;
        if (indicatorDigits[i] < 0)
        {
          indicatorDigits[i] = 9;
        }
      }
      delay(BURN_LOOP_DELAY);
    }
  }
}
