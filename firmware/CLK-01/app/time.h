#ifndef time_h
#define time_h

#include <timer2Minim.h>
#include <RTClib.h>

struct TimeTickResult
{
  bool changed;
  int8_t hrs;
  int8_t mins;
  int8_t secs;
  bool isNewHour;
};

class Time
{
public:
  Time() : timeTimer(1000)
  {
  }

  void setup()
  {
    setupRtc();
  }

  TimeTickResult tick()
  {
    timeJustChanged = false;
    if (!timeTimer.isReady())
    {
      return {false, hrs, mins, secs, false};
    }
#if DEBUG_EFFECTS
    secs = secs + 10;
#else
    secs++;
#endif
    if (secs > 59)
    {
      timeJustChanged = true;
      secs = 0;
      mins++;
      minsForRtcSync++;

      if (minsForRtcSync >= SYNC_RTC_INTERVAL)
      {
        minsForRtcSync = 0;
        syncRtc();
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
    }

    return {timeJustChanged, hrs, mins, secs, timeJustChanged && mins == 0};
  }

  void setTime(int8_t newHrs, int8_t newMins)
  {
    hrs = newHrs;
    mins = newMins;
    secs = 0;
    rtc.adjust(DateTime(2019, 12, 5, hrs, mins, secs));
  }

  int8_t getHours()
  {
    return hrs;
  }

  int8_t getMinutes()
  {
    return mins;
  }

  int8_t getSeconds()
  {
    return secs;
  }

private:
  RTC_DS3231 rtc;
  timerMinim timeTimer;
  byte minsForRtcSync = 0;
  int8_t hrs, mins, secs;
  bool timeJustChanged;

  void setupRtc()
  {
    rtc.begin();
    if (rtc.lostPower())
    {
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    syncRtc();
  }

  void syncRtc()
  {
#if !DEBUG_EFFECTS
    DateTime now = rtc.now();
    secs = now.second();
    mins = now.minute();
    hrs = now.hour();
#endif
  }
};

Time time;

#endif
