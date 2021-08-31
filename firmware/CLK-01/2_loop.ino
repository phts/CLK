void loop()
{
  if (dotTimer.isReady())
  {
    calculateTime();
  }
  if (timeJustChanged && mode == MODE_CLOCK)
  {
    flipTick();
  }
  dotBrightTick();
  backlBrightTick();
  if (currentGlitchesState)
  {
    glitchTick();
  }
  buttonsTick();
  settingsTick();
}
