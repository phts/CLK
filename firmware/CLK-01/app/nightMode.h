#ifndef nightmode_h
#define nightmode_h

#define NIGHT_MODE_DISABLED 0
#define NIGHT_MODE_ENABLED 1

class NightMode
{
public:
  void setup(bool initialMode)
  {
    setEnabled(initialMode);
  }

  bool isEnabled()
  {
    return enabled;
  }

  bool isNight()
  {
    return night;
  }

  void toggle()
  {
    setEnabled(!enabled);
  }

  void apply(byte hrs)
  {
    if (!enabled)
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
  bool enabled;
  bool forceApply = false;
  bool night = false;

  void setEnabled(bool value)
  {
    enabled = value;
    forceApply = true;
  }
};

NightMode nightMode;

#endif
