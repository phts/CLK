#include <timer2Minim.h>
#include <GyverButton.h>
#include <Wire.h>
#include <RTClib.h>
#include <EEPROM.h>

RTC_DS3231 rtc;

byte currentEffectsMode = EFFECT_DECAY;
byte currentBklightMode = BKLIGHT_FLASH;
boolean currentGlitchesMode = GLITCHES_ON;

timerMinim timeTimer(1000);
timerMinim dotTimer(DOT_TIMER);
timerMinim dotBrightnessTimer(DOT_BRIGHTNESS_TIMER);
timerMinim bklightBrightnessTimer(30);
timerMinim flipTimer(EFFECTS_SPEED[currentEffectsMode]);
timerMinim glitchTimer(1000);
timerMinim modeAdjustBlinkTimer(500);

GButton btnMode(PIN_BTN_MODE, HIGH_PULL, NORM_OPEN);
GButton btnBklight(PIN_BTN_BKLIGHT, HIGH_PULL, NORM_OPEN);
GButton btnEffects(PIN_BTN_EFFECTS, HIGH_PULL, NORM_OPEN);

volatile int8_t indicatorBrightness[4]; // 0--24
volatile int8_t indicatorDigits[4];     // 0--9

int8_t hrs, mins, secs;
byte indicatorMaxBrightness = INDICATOR_BRIGHTNESS;
byte dotMaxBrightness = DOT_BRIGHTNESS;
byte bklightMaxBrightness = BKLIGHT_BRIGHTNESS;
boolean timeJustChanged;
byte newTime[4];
byte mode = MODE_CLOCK;
boolean anodeStates[] = {1, 1, 1, 1};

const uint8_t CRTgamma[256] PROGMEM = {
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    3,
    3,
    3,
    3,
    3,
    3,
    4,
    4,
    4,
    4,
    4,
    5,
    5,
    5,
    5,
    6,
    6,
    6,
    7,
    7,
    7,
    8,
    8,
    8,
    9,
    9,
    9,
    10,
    10,
    10,
    11,
    11,
    12,
    12,
    12,
    13,
    13,
    14,
    14,
    15,
    15,
    16,
    16,
    17,
    17,
    18,
    18,
    19,
    19,
    20,
    20,
    21,
    22,
    22,
    23,
    23,
    24,
    25,
    25,
    26,
    26,
    27,
    28,
    28,
    29,
    30,
    30,
    31,
    32,
    33,
    33,
    34,
    35,
    35,
    36,
    37,
    38,
    39,
    39,
    40,
    41,
    42,
    43,
    43,
    44,
    45,
    46,
    47,
    48,
    49,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    65,
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    74,
    75,
    76,
    77,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    87,
    88,
    89,
    90,
    91,
    93,
    94,
    95,
    96,
    98,
    99,
    100,
    101,
    103,
    104,
    105,
    107,
    108,
    109,
    110,
    112,
    113,
    115,
    116,
    117,
    119,
    120,
    121,
    123,
    124,
    126,
    127,
    129,
    130,
    131,
    133,
    134,
    136,
    137,
    139,
    140,
    142,
    143,
    145,
    146,
    148,
    149,
    151,
    153,
    154,
    156,
    157,
    159,
    161,
    162,
    164,
    165,
    167,
    169,
    170,
    172,
    174,
    175,
    177,
    179,
    180,
    182,
    184,
    186,
    187,
    189,
    191,
    193,
    194,
    196,
    198,
    200,
    202,
    203,
    205,
    207,
    209,
    211,
    213,
    214,
    216,
    218,
    220,
    222,
    224,
    226,
    228,
    230,
    232,
    233,
    235,
    237,
    239,
    241,
    243,
    245,
    247,
    249,
    251,
    253,
    255,
};
