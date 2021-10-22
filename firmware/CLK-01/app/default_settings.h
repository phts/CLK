#ifndef default_settings_h
#define default_settings_h

#define DEBUG DEBUG_OFF

#define INITIAL_EFFECTS_MODE EFFECT_LOOP_C;
#define INITIAL_BKLIGHT_MODE BKLIGHT_ON;
#define INITIAL_GLITCHES_MODE GLITCHES_ON;

#define DUTY_CYCLE 180 // 175V for 180, 145V for 120

#define NIGHT_MODE NIGHT_MODE_ENABLED
#define NIGHT_START 23
#define NIGHT_END 7

#define INDICATOR_BRIGHTNESS 23      // 1--24
#define INDICATOR_BRIGHTNESS_NIGHT 3 // 1--24

#define DOT_BRIGHTNESS 35       // 1--255
#define DOT_BRIGHTNESS_NIGHT 15 // 1--255

#define BKLIGHT_BRIGHTNESS 150      // 0--255
#define BKLIGHT_BRIGHTNESS_NIGHT 50 // 0--255, 0=off
#define BKLIGHT_MIN_BRIGHTNESS 20   // 0--255
#define BKLIGHT_DELAY 400           // milliseconds
#define BKLIGHT_PERIOD 10000        // milliseconds
#define BKLIGHT_STEPS 2

#define GLITCH_MIN_INTERVAL 30  // seconds
#define GLITCH_MAX_INTERVAL 120 // seconds

#define DOT_MODE DOT_MODE_SIMPLE
#define DOT_INTERVAL 2000          // milliseconds
#define DOT_BRIGHTNESS_INTERVAL 20 // milliseconds

#define BURN_TIMES_IN_HOUR 3
#define BURN_LOOP_DELAY 10 // milliseconds
#define BURN_LOOPS 3

#define SYNC_RTC_INTERVAL 15 // minutes

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
#define DECODER_PIN_7 A0
#define DECODER_PIN_6 A1
#define DECODER_PIN_4 A2
#define DECODER_PIN_3 A3

#define MEMORY MEMORY_ENABLED
#define MEMORY_CELL_FIRST_RUN 1023
#define MEMORY_FLAG_FIRST_RUN 100

#define ADJ_TIME_MINS_INTERVAL 80
#define ADJ_TIME_MINS_HOLD_TIME 200
#define ADJ_TIME_HOURS_INTERVAL 150
#define ADJ_TIME_HOURS_HOLD_TIME 200

#endif
