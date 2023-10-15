#ifndef memory_h
#define memory_h

#include <EEPROM.h>

#define MEMORY_DISABLED 0
#define MEMORY_ENABLED 1

#define MEMORY_CELL_EFFECTS 0
#define MEMORY_CELL_BKLIGHT 1
#define MEMORY_CELL_GLITCHES 2
#define MEMORY_CELL_NIGHTMODE 3

struct StoredData
{
  byte effectsMode;
  byte bklightMode;
  bool glitchesMode;
  byte nightmodeMode;
};

class Memory
{
public:
  StoredData setup(byte initialEffectsMode, byte initialBklightMode, bool initialGlitchesMode, byte initialNightmodeMode)
  {
#if MEMORY == MEMORY_DISABLED
    return {initialEffectsMode, initialBklightMode, initialGlitchesMode, initialNightmodeMode};
#else
    if (EEPROM.read(MEMORY_CELL_FIRST_RUN) != MEMORY_FLAG_FIRST_RUN)
    {
      EEPROM.put(MEMORY_CELL_FIRST_RUN, MEMORY_FLAG_FIRST_RUN);
      EEPROM.put(MEMORY_CELL_EFFECTS, initialEffectsMode);
      EEPROM.put(MEMORY_CELL_BKLIGHT, initialBklightMode);
      EEPROM.put(MEMORY_CELL_GLITCHES, initialGlitchesMode);
      EEPROM.put(MEMORY_CELL_NIGHTMODE, initialNightmodeMode);
    }
    byte newEffectMode, newBklightMode, newGlitchesMode, newNightMode;
    EEPROM.get(MEMORY_CELL_EFFECTS, newEffectMode);
    EEPROM.get(MEMORY_CELL_BKLIGHT, newBklightMode);
    EEPROM.get(MEMORY_CELL_GLITCHES, newGlitchesMode);
    EEPROM.get(MEMORY_CELL_NIGHTMODE, newNightMode);
    debug(F("Memory -> effects mode"), newEffectMode);
    debug(F("Memory -> bklight mode"), newBklightMode);
    debug(F("Memory -> glitches mode"), newGlitchesMode);
    debug(F("Memory -> night mode"), newNightMode);
    return {newEffectMode, newBklightMode, newGlitchesMode, newNightMode};
#endif
  }

#if MEMORY == MEMORY_ENABLED
  void storeEffects(byte value)
  {
    EEPROM.put(MEMORY_CELL_EFFECTS, value);
  }
  void storeBacklight(byte value)
  {
    EEPROM.put(MEMORY_CELL_BKLIGHT, value);
  }
  void storeGlitches(byte value)
  {
    EEPROM.put(MEMORY_CELL_GLITCHES, value);
  }
  void storeNightMode(byte value)
  {
    EEPROM.put(MEMORY_CELL_NIGHTMODE, value);
  }
#else
  void storeEffects(byte value)
  {
  }
  void storeBacklight(byte value) {}
  void storeGlitches(byte value) {}
  void storeNightMode(byte value) {}
#endif
};

Memory memory;

#endif
