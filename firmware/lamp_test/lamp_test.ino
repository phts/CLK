#define DELAY 1000
#define DUTY_CYCLE 180

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

const byte DIGIT_TO_DECODER_VALUE[] = {3, 2, 7, 4, 1, 9, 8, 0, 5, 6};
byte INDICATOR_PINS[] = {PIN_HRS_L, PIN_HRS_R, PIN_MINS_L, PIN_MINS_R};

#include "GyverHacks.h"

void setDig(byte digit)
{
  digit = DIGIT_TO_DECODER_VALUE[digit];
  setPin(DECODER_PIN_3, bitRead(digit, 0));
  setPin(DECODER_PIN_6, bitRead(digit, 1));
  setPin(DECODER_PIN_7, bitRead(digit, 2));
  setPin(DECODER_PIN_4, bitRead(digit, 3));
}

void setup()
{
  Serial.begin(9600);
  pinMode(DECODER_PIN_7, OUTPUT);
  pinMode(DECODER_PIN_6, OUTPUT);
  pinMode(DECODER_PIN_4, OUTPUT);
  pinMode(DECODER_PIN_3, OUTPUT);
  pinMode(PIN_HRS_L, OUTPUT);
  pinMode(PIN_HRS_R, OUTPUT);
  pinMode(PIN_MINS_L, OUTPUT);
  pinMode(PIN_MINS_R, OUTPUT);
  pinMode(PIN_GEN, OUTPUT);
  pinMode(PIN_DOT, OUTPUT);
  pinMode(PIN_BKLIGHT, OUTPUT);
  TCCR1B = TCCR1B & 0b11111000 | 1; // ставим делитель 1
  setPWM(9, DUTY_CYCLE);
  setPWM(PIN_BKLIGHT, 1);
  setPWM(PIN_DOT, 1);
}

void loop()
{
  for (byte i = 0; i < 4; i++)
  {
    setPin(INDICATOR_PINS[i], 1);
    for (byte k = 0; k < 10; k++)
    {
      setDig(k);
      Serial.println("ind #" + String(i) + " digit: " + String(k));
      delay(DELAY);
    }
    setPin(INDICATOR_PINS[i], 0);
  }
}
