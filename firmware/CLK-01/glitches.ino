byte glitchCounter, glitchMax, glitchIndic;
boolean glitchFlag, indiState;

void glitchTick()
{
  if (!glitchFlag && secs > 7 && secs < 55)
  {
    if (glitchTimer.isReady())
    {
      glitchFlag = true;
      indiState = 0;
      glitchCounter = 0;
      glitchMax = random(2, 6);
      glitchIndic = random(0, 4);
      glitchTimer.setInterval(random(1, 6) * 20);
    }
  }
  else if (glitchFlag && glitchTimer.isReady())
  {
    indicatorBrightness[glitchIndic] = indiState * indicatorMaxBrightness;
    indiState = !indiState;
    glitchTimer.setInterval(random(1, 6) * 20);
    glitchCounter++;
    if (glitchCounter > glitchMax)
    {
      glitchTimer.setInterval(random(GLITCH_MIN_INTERVAL * 1000L, GLITCH_MAX_INTERVAL * 1000L));
      glitchFlag = false;
      indicatorBrightness[glitchIndic] = indicatorMaxBrightness;
    }
  }
}
