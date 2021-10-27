#ifndef memory_h
#define memory_h

#include <EEPROM.h>

#define MEMORY_DISABLED 0
#define MEMORY_ENABLED 1

#define MEMORY_CELL_EFFECTS 0
#define MEMORY_CELL_BKLIGHT 1
#define MEMORY_CELL_GLITCHES 2

struct StoredData
{
  byte effectsMode;
  byte bklightMode;
  boolean glitchesMode;
};

class Memory
{
public:
  StoredData setup(byte initialEffectsMode, byte initialBklightMode, boolean initialGlitchesMode)
  {
#if MEMORY == MEMORY_DISABLED
    return {initialEffectsMode, initialBklightMode, initialGlitchesMode};
#else
    if (EEPROM.read(MEMORY_CELL_FIRST_RUN) != MEMORY_FLAG_FIRST_RUN)
    {
      EEPROM.put(MEMORY_CELL_FIRST_RUN, MEMORY_FLAG_FIRST_RUN);
      EEPROM.put(MEMORY_CELL_EFFECTS, initialEffectsMode);
      EEPROM.put(MEMORY_CELL_BKLIGHT, initialBklightMode);
      EEPROM.put(MEMORY_CELL_GLITCHES, initialGlitchesMode);
    }
    byte newEffectMode, newBklightMode, newGlitchesMode;
    EEPROM.get(MEMORY_CELL_EFFECTS, newEffectMode);
    EEPROM.get(MEMORY_CELL_BKLIGHT, newBklightMode);
    EEPROM.get(MEMORY_CELL_GLITCHES, newGlitchesMode);
    return {newEffectMode, newBklightMode, newGlitchesMode};
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
#else
  void storeEffects(byte value)
  {
  }
  void storeBacklight(byte value) {}
  void storeGlitches(byte value) {}
#endif
};

Memory memory;

#endif
