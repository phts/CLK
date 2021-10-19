void loop()
{
  timeTick();
  if (timeJustChanged && mode == MODE_CLOCK)
  {
    flipTick();
  }
  dotTick();
  bklightBrightnessTick();
  if (currentGlitchesState)
  {
    glitchTick();
  }
  buttonsTick();
  settingsTick();
}
