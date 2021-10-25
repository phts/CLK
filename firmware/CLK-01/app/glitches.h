#ifndef glitches_h
#define glitches_h

#include <timer2Minim.h>

#define GLITCHES_OFF 0
#define GLITCHES_ON 1

class Glitches
{
public:
  Glitches() : timer(1000)
  {
  }

  void setup(boolean initialMode)
  {
    mode = initialMode;
    timer.setInterval(random(GLITCH_MIN_INTERVAL * 1000L, GLITCH_MAX_INTERVAL * 1000L));
  }

  void toggle()
  {
    setMode(!mode);
  }

  boolean getMode()
  {
    return mode;
  }

  void setMode(byte newValue)
  {
    mode = newValue;
  }

  void tick()
  {
    if (mode != GLITCHES_ON)
    {
      return;
    }
    byte secs = time.getSeconds();
    if (!glitchFlag && secs > 7 && secs < 55)
    {
      if (timer.isReady())
      {
        glitchFlag = true;
        indiState = 0;
        glitchCounter = 0;
        glitchMax = random(2, 6);
        glitchIndic = random(0, 4);
        timer.setInterval(random(1, 6) * 20);
      }
    }
    else if (glitchFlag && timer.isReady())
    {
      indicatorBrightness[glitchIndic] = indiState * indicatorMaxBrightness;
      indiState = !indiState;
      timer.setInterval(random(1, 6) * 20);
      glitchCounter++;
      if (glitchCounter > glitchMax)
      {
        timer.setInterval(random(GLITCH_MIN_INTERVAL * 1000L, GLITCH_MAX_INTERVAL * 1000L));
        glitchFlag = false;
        indicatorBrightness[glitchIndic] = indicatorMaxBrightness;
      }
    }
  }

private:
  timerMinim timer;
  boolean mode;
  byte glitchCounter;
  byte glitchMax;
  byte glitchIndic;
  boolean glitchFlag;
  boolean indiState;
};

Glitches glitches;

#endif
