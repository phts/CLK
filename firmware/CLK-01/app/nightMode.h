#ifndef nightmode_h
#define nightmode_h

#define NIGHT_MODE_DISABLED 0
#define NIGHT_MODE_ENABLED 1
#define NIGHT_MODE_NIGHTLIGHT 2
#define NIGHT_MODE_AMOUNT 3

class NightMode
{
public:
  void setup(byte initialMode)
  {
    setMode(initialMode);
  }

  byte getMode()
  {
    return mode;
  }

  bool isNight()
  {
    return night;
  }

  bool isNightlight()
  {
    return mode == NIGHT_MODE_NIGHTLIGHT;
  }

  void toggle()
  {
    byte newMode = mode + 1;
    setMode(newMode >= NIGHT_MODE_AMOUNT ? 0 : newMode);
  }

  void apply(byte hrs)
  {
    if (mode == NIGHT_MODE_DISABLED)
    {
      night = false;
      return;
    }
    night = (hrs >= NIGHT_START && hrs <= 23) || (hrs >= 0 && hrs < NIGHT_END);
  }

  void tick(bool isNewHour, byte hrs)
  {
    if (!(isNewHour || forceApply))
    {
      return;
    }
    forceApply = false;
    apply(hrs);
  }

private:
  byte mode;
  bool forceApply = false;
  bool night = false;

  void setMode(byte value)
  {
    mode = value;
    forceApply = true;
  }
};

NightMode nightMode;

#endif
