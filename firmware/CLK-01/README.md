# PHTS CLK-01

<center><image width="400" src="https://image.easyeda.com/pullimage/eZfHBXqBWeyuq8u5oUy41QWFKAyJxHvFhsioJCOD.jpeg"></center>

<center><i>Work in progress</i></center>

## Hardware

Hosted on [EasyEDA/phts/CLK-01].

![PHTS CLK-01](https://image.easyeda.com/documents/f8e8fa42a9a74f4194dbb38830f3f9a2.png)

## Control

### "Clock" mode

Single click on button "EFFECTS" selects effects when minutes change:

- None
- Decay
- Loop through digits
- Loop through cathodes
- Train
- Rubber band

Single click on button "BKLIGHT" selects backlight:

- Turned off
- Turned on (100%)
- Turned on (60%)
- Turned on (30%)
- Smooth flashing

Holding button "EFFECTS" toggles glitches on/off.

### "Set" mode

Single click on button "HOURS" increases hour value.

Single click on button "MINUTES" increases minute value.

## Settings

| Name                         |      Values | Description                                                           |
| ---------------------------- | ----------: | --------------------------------------------------------------------- |
| `BKLIGHT_BRIGHTNESS_NIGHT`   | 0&ndash;255 | Backlight brightness on nighttime                                     |
| `BKLIGHT_BRIGHTNESS`         | 0&ndash;255 | Backlight brightness on daytime                                       |
| `BKLIGHT_DELAY`              |          ms | How long backlight flashing should wait between                       |
| `BKLIGHT_MIN_BRIGHTNESS`     | 0&ndash;255 | Minimal backlight brightness (flashing mode)                          |
| `BKLIGHT_PERIOD`             |          ms | How fast backlight should blink (flashing mode)                       |
| `BKLIGHT_STEPS`              |             | How smooth backlight should be changed (flashing mode)                |
| `BURN_LOOP_DELAY`            |          ms | How long to wait between "burn" loops                                 |
| `BURN_LOOPS`                 |             | How many loops to run "burn"                                          |
| `BURN_TIMES_PER_HOUR`        |             | How many times need to burn indicators during an hour                 |
| `DEBUG`                      |             | If enabled, prints debug messages into Serial port                    |
| `DOT_BRIGHTNESS_INTERVAL`    |          ms | How fast dot brightness should change during blinking (smooth mode)   |
| `DOT_BRIGHTNESS_NIGHT`       | 0&ndash;255 | Dot brightness on nighttime                                           |
| `DOT_BRIGHTNESS`             | 0&ndash;255 | Dot brightness on daytime                                             |
| `DOT_INTERVAL`               |          ms | How fast dot should blink                                             |
| `DOT_MODE`                   |             | How to blink - simple or smooth                                       |
| `DUTY_CYCLE`                 | 0&ndash;255 | Generator duty cycle, affects total voltage which comes to indicators |
| `GLITCH_MAX_INTERVAL`        |     seconds | Interval between glitches picked randomly (max value)                 |
| `GLITCH_MIN_INTERVAL`        |     seconds | Interval between glitches picked randomly (min value)                 |
| `INDICATOR_BRIGHTNESS_NIGHT` |  0&ndash;24 | Indicator brightness on nighttime                                     |
| `INDICATOR_BRIGHTNESS`       |  0&ndash;24 | Indicator brightness on daytime                                       |
| `INITIAL_BKLIGHT_MODE`       |             |                                                                       |
| `INITIAL_EFFECTS_MODE`       |             |                                                                       |
| `INITIAL_GLITCHES_MODE`      |             |                                                                       |
| `MEMORY_CELL_FIRST_RUN`      |             | Memory cell where to store "first run" flag                           |
| `MEMORY_FLAG_FIRST_RUN`      |             | Value of "first run" flag                                             |
| `MEMORY`                     |             | Whether enabled memory storage or not                                 |
| `MODE_SET_BLINK_INTERVAL`    |          ms | How fast indicators blink during "Set" mode                           |
| `MODE_SET_HOURS_HOLD_TIME`   |          ms | How long need to hold button to start repeating                       |
| `MODE_SET_HOURS_INTERVAL`    |          ms | How fast values are changed while button is pressed                   |
| `MODE_SET_MINS_HOLD_TIME`    |          ms | How long need to hold button to start repeating                       |
| `MODE_SET_MINS_INTERVAL`     |          ms | How fast values are changed while button is pressed                   |
| `NIGHT_END`                  |  0&ndash;23 | Hour when night mode should end                                       |
| `NIGHT_MODE`                 |             | Whether enabled night mode (dim all indicators) or not                |
| `NIGHT_START`                |  0&ndash;23 | Hour when night mode should start                                     |
| `SYNC_RTC_INTERVAL`          |     minutes | How frequent to sync time with RTC module                             |

### Override settings locally

Clone `settings.h.example` into `settings.h` and redefine variables.

[easyeda/phts/clk-01]: https://oshwlab.com/phts/CLK-01
