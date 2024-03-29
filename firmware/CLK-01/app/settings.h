#ifndef settings_h
#define settings_h

#define VERSION "Unknown"
#define DEBUG false
#define DEBUG_EFFECTS false
#define DEBUG_STANDBY_ENABLED false

#define INITIAL_EFFECTS_MODE EFFECT_LOOP_CATHODES
#define INITIAL_BKLIGHT_MODE BKLIGHT_ON
#define INITIAL_GLITCHES_MODE GLITCHES_ON
#define INITIAL_NIGHT_MODE NIGHT_MODE_ENABLED

#define DUTY_CYCLE 180

#define NIGHT_START 22
#define NIGHT_END 7

#define INDICATOR_BRIGHTNESS 23
#define INDICATOR_BRIGHTNESS_NIGHT 3

#define DOT_BRIGHTNESS 35
#define DOT_BRIGHTNESS_NIGHT 15

#define BKLIGHT_BRIGHTNESS 150
#define BKLIGHT_BRIGHTNESS_NIGHT 0
#define BKLIGHT_MIN_BRIGHTNESS 20
#define BKLIGHT_DELAY 400
#define BKLIGHT_PERIOD 10000
#define BKLIGHT_STEPS 2

#define GLITCH_MIN_INTERVAL 30
#define GLITCH_MAX_INTERVAL 120

#define DOT_MODE DOT_MODE_SIMPLE
#define DOT_INTERVAL 2000
#define DOT_BRIGHTNESS_INTERVAL 20

#define BURN_TIMES_PER_HOUR 3
#define BURN_LOOP_DELAY 10
#define BURN_LOOPS 3

#define SYNC_RTC_INTERVAL 15

#define PIN_SW_STANDBY 2
#define PIN_HRS_L 3
#define PIN_HRS_R 4
#define PIN_MINS_L 5
#define PIN_MINS_R 6
#define PIN_SW_MODE 7
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

#define MODE_SET_BLINK_INTERVAL 1000
#define MODE_SET_MINS_INTERVAL 80
#define MODE_SET_MINS_HOLD_TIME 200
#define MODE_SET_HOURS_INTERVAL 150
#define MODE_SET_HOURS_HOLD_TIME 200

#define STANDBY_KEEP_BKLIGHT true
#define STANDBY_KEEP_DOT true
#define STANDBY_NIGHT_SLEEP true
#define STANDBY_TIMEOUT 300
#define STANDBY_WAKEUP_ON_TIME_CHANGE true
#define STANDBY_WAKEUP_ON_TIME_CHANGE_MINS 60
#define STANDBY_WAKEUP_RANDOM true
#define STANDBY_WAKEUP_RANDOM_TIMES 2

#define CONFIRMATION_INTERVAL 200

#endif
