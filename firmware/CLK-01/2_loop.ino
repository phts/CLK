void loop()
{
  if (dotTimer.isReady())
  {
    timeTick();
  }
  if (timeJustChanged && mode == MODE_CLOCK)
  {
    flipTick();
  }
  dotBrightnessTick();
  bklightBrightnessTick();
  if (currentGlitchesState)
  {
    glitchTick();
  }
  buttonsTick();
  settingsTick();
}
