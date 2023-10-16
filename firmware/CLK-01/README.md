# PHTS CLK-01

<center><image width="400" src="https://image.easyeda.com/pullimage/DY2cV2TE9SzW4QEGUBPfhBxzWKnjN2z8livtnTUQ.jpeg"></center>

## Hardware

Hosted on [EasyEDA/phts/CLK-01].

![PHTS CLK-01](https://image.easyeda.com/documents/f8e8fa42a9a74f4194dbb38830f3f9a2.png)

## Owner's manual

Available at: [phts.github.io/CLK/CLK-01/Manual.pdf][manual]

## Usage

### Control

#### "CLOCK" mode

Single click on button "EFFECTS / GLITCHES" selects effects on flip time:

0. None (immediately)
1. Decay
2. Loop through digits
3. Loop through digits (reversed)
4. Loop through cathodes (shortest distance)
5. Loop through cathodes (at least 1 loop)
6. Loop through cathodes (ping-pong)
7. Train
8. Rubber band

Holding button "EFFECTS / GLITCHES" toggles glitches on/off.

Single click on button "BKLIGHT / NIGHT M." selects backlight:

0. Turned off
1. Turned on (100%)
2. Turned on (60%)
3. Turned on (30%)
4. Smooth flashing

Holding button "BKLIGHT / NIGHT M." toggles night mode:

0. Disabled
1. Enabled
2. Nightlight mode

#### "TIME SET" mode

Single click on button "HOURS" increases hour value.

Single click on button "MINUTES" increases minute value.

To apply new time toggle "MODE" switch to "CLOCK" position.

## Development

1. Connect device to PC. Find and install [USB-SERIAL CH340 driver] to be able to use the device via a COM port.

2. Open `CLK-01.ino` file in Arduino IDE or any other editor supported by Arduino. Set the following parameters:

   1. Board type: `Arduino Nano`
   2. Processor: `ATmega 328P (Old Bootloader)`
   3. Programmer: `AVRISP mkII`
   4. Port: corresponding port which was assigned to the device when connected

3. Make your cool changes and upload the firmware to device

### Settings

| Name                                 |                                                                                                                                                                                  Values | Description                                                                                                                                                                                                |
| ------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `BKLIGHT_BRIGHTNESS_NIGHT`           |                                                                                                                                                                             0&ndash;255 | Backlight brightness on nighttime                                                                                                                                                                          |
| `BKLIGHT_BRIGHTNESS`                 |                                                                                                                                                                             0&ndash;255 | Backlight brightness on daytime                                                                                                                                                                            |
| `BKLIGHT_DELAY`                      |                                                                                                                                                                                      ms | How long backlight flashing should wait between                                                                                                                                                            |
| `BKLIGHT_MIN_BRIGHTNESS`             |                                                                                                                                                                             0&ndash;255 | Minimal backlight brightness (flashing mode)                                                                                                                                                               |
| `BKLIGHT_PERIOD`                     |                                                                                                                                                                                      ms | How fast backlight should blink (flashing mode)                                                                                                                                                            |
| `BKLIGHT_STEPS`                      |                                                                                                                                                                                         | How smooth backlight should be changed (flashing mode)                                                                                                                                                     |
| `BURN_LOOP_DELAY`                    |                                                                                                                                                                                      ms | How long to wait between "burn" loops                                                                                                                                                                      |
| `BURN_LOOPS`                         |                                                                                                                                                                                         | How many loops to run "burn"                                                                                                                                                                               |
| `BURN_TIMES_PER_HOUR`                |                                                                                                                                                                                         | How many times need to burn indicators during an hour                                                                                                                                                      |
| `CONFIRMATION_INTERVAL`              |                                                                                                                                                                                      ms | How fast control button press confirmation is blinking                                                                                                                                                     |
| `DEBUG`                              |                                                                                                                                                                                 Boolean | If enabled, prints debug messages into Serial port                                                                                                                                                         |
| `DEBUG_EFFECTS`                      |                                                                                                                                                                                 Boolean | If enabled, makes time changed every few seconds                                                                                                                                                           |
| `DEBUG_STANDBY_ENABLED`              |                                                                                                                                                                                 Boolean | If enabled, makes STADBY mode always enabled                                                                                                                                                               |
| `DOT_BRIGHTNESS_INTERVAL`            |                                                                                                                                                                                      ms | How fast dot brightness should change during blinking (smooth mode)                                                                                                                                        |
| `DOT_BRIGHTNESS_NIGHT`               |                                                                                                                                                                             0&ndash;255 | Dot brightness on nighttime                                                                                                                                                                                |
| `DOT_BRIGHTNESS`                     |                                                                                                                                                                             0&ndash;255 | Dot brightness on daytime                                                                                                                                                                                  |
| `DOT_INTERVAL`                       |                                                                                                                                                                                      ms | How fast dot should blink                                                                                                                                                                                  |
| `DOT_MODE`                           |                                                                                                                                                                                         | How to blink - simple or smooth                                                                                                                                                                            |
| `DUTY_CYCLE`                         |                                                                                                                                                                             0&ndash;255 | Generator duty cycle, affects total voltage which comes to indicators                                                                                                                                      |
| `GLITCH_MAX_INTERVAL`                |                                                                                                                                                                                 seconds | Interval between glitches picked randomly (max value)                                                                                                                                                      |
| `GLITCH_MIN_INTERVAL`                |                                                                                                                                                                                 seconds | Interval between glitches picked randomly (min value)                                                                                                                                                      |
| `INDICATOR_BRIGHTNESS_NIGHT`         |                                                                                                                                                                              0&ndash;24 | Indicator brightness on nighttime                                                                                                                                                                          |
| `INDICATOR_BRIGHTNESS`               |                                                                                                                                                                              0&ndash;24 | Indicator brightness on daytime                                                                                                                                                                            |
| `INITIAL_BKLIGHT_MODE`               |                                                                                                              `BKLIGHT_OFF` `BKLIGHT_ON` `BKLIGHT_ON_60` `BKLIGHT_ON_30` `BKLIGHT_FLASH` | Initial Backlight mode on fresh device's start                                                                                                                                                             |
| `INITIAL_EFFECTS_MODE`               | `EFFECT_NONE` `EFFECT_DECAY` `EFFECT_LOOP_DIGITS` `EFFECT_LOOP_DIGITS_REV` `EFFECT_LOOP_CATHODES` `EFFECT_LOOP_CATHODES_LONG` `EFFECT_PINGPONG_CATHODES` `EFFECT_TRAIN` `EFFECT_RUBBER` | Initial Effects mode on fresh device's start                                                                                                                                                               |
| `INITIAL_GLITCHES_MODE`              |                                                                                                                                                            `GLITCHES_OFF` `GLITCHES_ON` | Initial Glitches mode on fresh device's start                                                                                                                                                              |
| `INITIAL_NIGHT_MODE`                 |                                                                                                                      `NIGHT_MODE_DISABLED` `NIGHT_MODE_ENABLED` `NIGHT_MODE_NIGHTLIGHT` | Initial Night mode on fresh device's start                                                                                                                                                                 |
| `MEMORY_CELL_FIRST_RUN`              |                                                                                                                                                                                         | Memory cell where to store "first run" flag                                                                                                                                                                |
| `MEMORY_FLAG_FIRST_RUN`              |                                                                                                                                                                                         | Value of "first run" flag                                                                                                                                                                                  |
| `MEMORY`                             |                                                                                                                                                                                         | Whether enabled memory storage or not                                                                                                                                                                      |
| `MODE_SET_BLINK_INTERVAL`            |                                                                                                                                                                                      ms | How fast indicators blink during "Set" mode                                                                                                                                                                |
| `MODE_SET_HOURS_HOLD_TIME`           |                                                                                                                                                                                      ms | How long need to hold button to start repeating                                                                                                                                                            |
| `MODE_SET_HOURS_INTERVAL`            |                                                                                                                                                                                      ms | How fast values are changed while button is pressed                                                                                                                                                        |
| `MODE_SET_MINS_HOLD_TIME`            |                                                                                                                                                                                      ms | How long need to hold button to start repeating                                                                                                                                                            |
| `MODE_SET_MINS_INTERVAL`             |                                                                                                                                                                                      ms | How fast values are changed while button is pressed                                                                                                                                                        |
| `NIGHT_END`                          |                                                                                                                                                                              0&ndash;23 | Hour when night mode should end                                                                                                                                                                            |
| `NIGHT_START`                        |                                                                                                                                                                              0&ndash;23 | Hour when night mode should start                                                                                                                                                                          |
| `STANDBY_KEEP_BKLIGHT`               |                                                                                                                                                                                 Boolean | Whether to keep backlight on or off during standby mode                                                                                                                                                    |
| `STANDBY_KEEP_DOT`                   |                                                                                                                                                                                 Boolean | Whether to keep dot on or off during standby mode                                                                                                                                                          |
| `STANDBY_NIGHT_SLEEP`                |                                                                                                                                                                                 Boolean | Whether to make the device have completely no light during night when Night Mode is enabled                                                                                                                |
| `STANDBY_TIMEOUT`                    |                                                                                                                                                                                 seconds | Time of inactivity to enter to standby mode                                                                                                                                                                |
| `STANDBY_WAKEUP_ON_TIME_CHANGE`      |                                                                                                                                                                                 Boolean | Whether to wake up from standby when time changed on exact minutes (controlled by `STANDBY_WAKEUP_ON_TIME_CHANGE_MINS`)                                                                                    |
| `STANDBY_WAKEUP_ON_TIME_CHANGE_MINS` |                                                                                                                                                                              1&ndash;60 | Minutes when the device wakes up from standby mode. E.g. `10` means to wake up on `:00`, `:10`, `:20`, ...; `49` means to wake up on `:00`, `:49`; `60` means to wake up on `:00`; value `0` is forbidden. |
| `STANDBY_WAKEUP_RANDOM`              |                                                                                                                                                                                 Boolean | Whether to wake up at random minutes several times (controlled by `STANDBY_WAKEUP_RANDOM_TIMES`)                                                                                                           |
| `STANDBY_WAKEUP_RANDOM_TIMES`        |                                                                                                                                                                                  Number | How many times per hour the device should wake up from standby mode at random minute                                                                                                                       |
| `SYNC_RTC_INTERVAL`                  |                                                                                                                                                                                 minutes | How frequent to sync time with RTC module                                                                                                                                                                  |

#### Override settings locally

Clone `local_settings.h.example` into `local_settings.h` and redefine variables.

[easyeda/phts/clk-01]: https://oshwlab.com/phts/CLK-01
[usb-serial ch340 driver]: https://www.google.com/search?q=USB-SERIAL+CH340
[manual]: https://phts.github.io/CLK/CLK-01/Manual.pdf
