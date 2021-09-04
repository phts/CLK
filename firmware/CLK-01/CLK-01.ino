#define DUTY_CYCLE 180 // 175V for 180, 145V for 120

#define EFFECT_NONE 0
#define EFFECT_DECAY 1
#define EFFECT_LOOP_D 2
#define EFFECT_LOOP_C 3
#define EFFECT_TRAIN 4
#define EFFECT_RUBBER 5

#define BKLIGHT_FLASH 0
#define BKLIGHT_ON 1
#define BKLIGHT_OFF 2

#define GLITCHES_OFF 0
#define GLITCHES_ON 1

#define NIGHT_LIGHT_OFF 0
#define NIGHT_LIGHT_ON 1
#define NIGHT_LIGHT NIGHT_LIGHT_ON
#define NIGHT_START 23
#define NIGHT_END 7

#define INDICATOR_BRIGHTNESS 23      // 1--24
#define INDICATOR_BRIGHTNESS_NIGHT 3 // 1--24

#define DOT_BRIGHTNESS 35       // 1--255
#define DOT_BRIGHTNESS_NIGHT 15 // 1--255

#define BKLIGHT_BRIGHTNESS 250      // 0--255
#define BKLIGHT_BRIGHTNESS_NIGHT 50 // 0--255, 0=off
#define BKLIGHT_MIN_BRIGHTNESS 20   // 0--255
#define BKLIGHT_DELAY 400           // milliseconds
#define BKLIGHT_PERIOD 5000         // milliseconds
#define BKLIGHT_STEPS 2

#define GLITCH_MIN_INTERVAL 30  // seconds
#define GLITCH_MAX_INTERVAL 120 // seconds

#define DOT_INTERVAL 500        // milliseconds
#define DOT_BRIGHTNESS_TIMER 20 // milliseconds

#define BURN_LOOP_DELAY 10 // milliseconds
#define BURN_LOOPS 3
#define BURN_PERIOD 15 // minutes

#define SYNC_RTC_INTERVAL 15 // minutes

byte EFFECTS_SPEED[] = {0, 130, 50, 40, 70, 70};
byte EFFECTS_SPEEDS_AMOUNT = sizeof(EFFECTS_SPEED);

#define PIN_HRS_L 3
#define PIN_HRS_R 4
#define PIN_MINS_L 5
#define PIN_MINS_R 6
#define PIN_BTN_MODE 7
#define PIN_BTN_BKLIGHT 8
#define PIN_GEN 9
#define PIN_DOT 10
#define PIN_BKLIGHT 11
#define PIN_BTN_EFFECTS 12
#define PIN_DECODER_0 A0
#define PIN_DECODER_1 A1
#define PIN_DECODER_2 A2
#define PIN_DECODER_3 A3

#define MEMORY_CELL_FIRST_RUN 1023
#define MEMORY_FLAG_FIRST_RUN 100
#define MEMORY_CELL_EFFECTS 0
#define MEMORY_CELL_BKLIGHT 1
#define MEMORY_CELL_GLITCHES 2

#define ADJ_TIME_MINS_INTERVAL 80
#define ADJ_TIME_MINS_TIMEOUT 200
#define ADJ_TIME_HOURS_INTERVAL 150
#define ADJ_TIME_HOURS_TIMEOUT 200

byte currentEffectsMode = EFFECT_DECAY;
byte currentBklightMode = BKLIGHT_FLASH;
boolean currentGlitchesState = GLITCHES_ON;

const byte DIGIT_TO_DECODER_VALUE[] = {7, 3, 6, 4, 1, 9, 8, 0, 5, 2};
