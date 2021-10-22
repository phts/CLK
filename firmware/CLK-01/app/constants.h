#ifndef constants_h
#define constants_h

#define DEBUG_OFF 0
#define DEBUG_ON 1

#define EFFECT_NONE 0
#define EFFECT_DECAY 1
#define EFFECT_LOOP_D 2
#define EFFECT_LOOP_C 3
#define EFFECT_TRAIN 4
#define EFFECT_RUBBER 5
#define EFFECT_AMOUNT 6

#define BKLIGHT_OFF 0
#define BKLIGHT_ON 1
#define BKLIGHT_ON_60 2
#define BKLIGHT_ON_30 3
#define BKLIGHT_FLASH 4
#define BKLIGHT_AMOUNT 5

#define GLITCHES_OFF 0
#define GLITCHES_ON 1

#define DOT_MODE_SIMPLE 0
#define DOT_MODE_SMOOTH 1

#define NIGHT_MODE_DISABLED 0
#define NIGHT_MODE_ENABLED 1

#define MEMORY_DISABLED 0
#define MEMORY_ENABLED 1

#define MEMORY_CELL_EFFECTS 0
#define MEMORY_CELL_BKLIGHT 1
#define MEMORY_CELL_GLITCHES 2

#define MODE_CLOCK 0
#define MODE_ADJUST 1

byte EFFECTS_SPEED[] = {0, 130, 50, 40, 70, 70};

#endif
