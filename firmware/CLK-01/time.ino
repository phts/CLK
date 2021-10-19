byte minsCount = 0;

void timeTick()
{
  if (!timeTimer.isReady())
  {
    return;
  }
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
    updateBrightness();
  }
  if (timeJustChanged)
  {
    setNewTime();
  }
}

void sendTime(byte hours, byte minutes)
{
  indicatorDigits[0] = (byte)hours / 10;
  indicatorDigits[1] = (byte)hours % 10;

  indicatorDigits[2] = (byte)minutes / 10;
  indicatorDigits[3] = (byte)minutes % 10;
}

void setNewTime()
{
  newTime[0] = (byte)hrs / 10;
  newTime[1] = (byte)hrs % 10;

  newTime[2] = (byte)mins / 10;
  newTime[3] = (byte)mins % 10;
}
