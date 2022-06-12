#ifndef debug_h
#define debug_h

#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)

void setupDebug()
{
  Serial.begin(9600);
  Serial.println(F("PHTS CLK-01"));
  Serial.println("Firmware uploaded: " __DATE__ " " __TIME__);
  Serial.println("Version: " VERSION);
  Serial.println(F("Settings:"));
  Serial.print(F("  DEBUG="));
  Serial.println(VALUE(DEBUG));
  Serial.print(F("  DEBUG_EFFECTS="));
  Serial.println(VALUE(DEBUG_EFFECTS));
  Serial.print(F("  INITIAL_EFFECTS_MODE="));
  Serial.println(VALUE(INITIAL_EFFECTS_MODE));
  Serial.print(F("  INITIAL_BKLIGHT_MODE="));
  Serial.println(VALUE(INITIAL_BKLIGHT_MODE));
  Serial.print(F("  INITIAL_GLITCHES_MODE="));
  Serial.println(VALUE(INITIAL_GLITCHES_MODE));
  Serial.print(F("  INITIAL_NIGHT_MODE="));
  Serial.println(VALUE(INITIAL_NIGHT_MODE));
  Serial.print(F("  DUTY_CYCLE="));
  Serial.println(String(DUTY_CYCLE));
  Serial.print(F("  NIGHT_START="));
  Serial.println(String(NIGHT_START));
  Serial.print(F("  NIGHT_END="));
  Serial.println(String(NIGHT_END));
  Serial.print(F("  INDICATOR_BRIGHTNESS="));
  Serial.println(String(INDICATOR_BRIGHTNESS));
  Serial.print(F("  INDICATOR_BRIGHTNESS_NIGHT="));
  Serial.println(String(INDICATOR_BRIGHTNESS_NIGHT));
  Serial.print(F("  DOT_BRIGHTNESS="));
  Serial.println(String(DOT_BRIGHTNESS));
  Serial.print(F("  DOT_BRIGHTNESS_NIGHT="));
  Serial.println(String(DOT_BRIGHTNESS_NIGHT));
  Serial.print(F("  BKLIGHT_BRIGHTNESS="));
  Serial.println(String(BKLIGHT_BRIGHTNESS));
  Serial.print(F("  BKLIGHT_BRIGHTNESS_NIGHT="));
  Serial.println(String(BKLIGHT_BRIGHTNESS_NIGHT));
  Serial.print(F("  BKLIGHT_MIN_BRIGHTNESS="));
  Serial.println(String(BKLIGHT_MIN_BRIGHTNESS));
  Serial.print(F("  BKLIGHT_DELAY="));
  Serial.println(String(BKLIGHT_DELAY));
  Serial.print(F("  BKLIGHT_PERIOD="));
  Serial.println(String(BKLIGHT_PERIOD));
  Serial.print(F("  BKLIGHT_STEPS="));
  Serial.println(String(BKLIGHT_STEPS));
  Serial.print(F("  GLITCH_MIN_INTERVAL="));
  Serial.println(String(GLITCH_MIN_INTERVAL));
  Serial.print(F("  GLITCH_MAX_INTERVAL="));
  Serial.println(String(GLITCH_MAX_INTERVAL));
  Serial.print(F("  DOT_MODE="));
  Serial.println(VALUE(DOT_MODE));
  Serial.print(F("  DOT_INTERVAL="));
  Serial.println(String(DOT_INTERVAL));
  Serial.print(F("  DOT_BRIGHTNESS_INTERVAL="));
  Serial.println(String(DOT_BRIGHTNESS_INTERVAL));
  Serial.print(F("  BURN_TIMES_PER_HOUR="));
  Serial.println(String(BURN_TIMES_PER_HOUR));
  Serial.print(F("  BURN_LOOP_DELAY="));
  Serial.println(String(BURN_LOOP_DELAY));
  Serial.print(F("  BURN_LOOPS="));
  Serial.println(String(BURN_LOOPS));
  Serial.print(F("  SYNC_RTC_INTERVAL="));
  Serial.println(String(SYNC_RTC_INTERVAL));
  Serial.print(F("  MEMORY="));
  Serial.println(VALUE(MEMORY));
  Serial.print(F("  MEMORY_CELL_FIRST_RUN="));
  Serial.println(String(MEMORY_CELL_FIRST_RUN));
  Serial.print(F("  MEMORY_FLAG_FIRST_RUN="));
  Serial.println(String(MEMORY_FLAG_FIRST_RUN));
  Serial.print(F("  MODE_SET_BLINK_INTERVAL="));
  Serial.println(String(MODE_SET_BLINK_INTERVAL));
  Serial.print(F("  MODE_SET_MINS_INTERVAL="));
  Serial.println(String(MODE_SET_MINS_INTERVAL));
  Serial.print(F("  MODE_SET_MINS_HOLD_TIME="));
  Serial.println(String(MODE_SET_MINS_HOLD_TIME));
  Serial.print(F("  MODE_SET_HOURS_INTERVAL="));
  Serial.println(String(MODE_SET_HOURS_INTERVAL));
  Serial.print(F("  MODE_SET_HOURS_HOLD_TIME="));
  Serial.println(String(MODE_SET_HOURS_HOLD_TIME));
  Serial.print(F("  STANDBY_KEEP_BKLIGHT="));
  Serial.println(String(STANDBY_KEEP_BKLIGHT));
  Serial.print(F("  STANDBY_KEEP_DOT="));
  Serial.println(String(STANDBY_KEEP_DOT));
  Serial.print(F("  STANDBY_TIMEOUT="));
  Serial.println(String(STANDBY_TIMEOUT));
  Serial.print(F("  STANDBY_WAKEUP_ON_TIME_CHANGE="));
  Serial.println(String(STANDBY_WAKEUP_ON_TIME_CHANGE));
  Serial.print(F("  STANDBY_WAKEUP_ON_TIME_CHANGE_MINS="));
  Serial.println(String(STANDBY_WAKEUP_ON_TIME_CHANGE_MINS));
}

#if DEBUG
void debug(byte number)
{
  Serial.println(String(number));
}

void debug(String str)
{
  Serial.println(str);
}

void debug(String label, String value)
{
  Serial.println(label + ": " + value);
}

void debug(String label, byte value)
{
  Serial.println(label + ": " + String(value));
}
#else
void debug(byte str)
{
}
void debug(String str)
{
}
void debug(String label, String value)
{
}
void debug(String label, byte value)
{
}
#endif

#endif
