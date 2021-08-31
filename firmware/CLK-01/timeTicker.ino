boolean isDotTurnedOn;
byte minsCount = 0;
void calculateTime()
{
  isDotTurnedOn = !isDotTurnedOn;
  if (isDotTurnedOn)
  {
    dotBrightFlag = true;
    dotBrightDirection = true;
    dotBrightCounter = 0;
    secs++;
    if (secs > 59)
    {
      timeJustChanged = true;
      secs = 0;
      mins++;
      minsCount++;

      if (minsCount >= SYNC_RTC_INTERVAL)
      {
        minsCount = 0;
        DateTime now = rtc.now();
        secs = now.second();
        mins = now.minute();
        hrs = now.hour();
      }

      if (mins % BURN_PERIOD == 0)
      {
        burnIndicators();
      }
    }
    if (mins > 59)
    {
      mins = 0;
      hrs++;
      if (hrs > 23)
      {
        hrs = 0;
      }
      changeBright();
    }
    if (timeJustChanged)
    {
      setNewTime();
    }
  }
}
