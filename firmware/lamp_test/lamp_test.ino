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
#define PIN_DECODER_0 A0
#define PIN_DECODER_1 A1
#define PIN_DECODER_2 A2
#define PIN_DECODER_3 A3

// распиновка ламп
byte DIGIT_TO_DECODER_VALUE[] = {7, 3, 6, 4, 1, 9, 8, 0, 5, 2};         // маска дешифратора платы in12_turned (цифры нормальные)
byte INDICATOR_PINS[] = {PIN_HRS_L, PIN_HRS_R, PIN_MINS_L, PIN_MINS_R}; // порядок индикаторов слева направо

#include "GyverHacks.h"

void setDig(byte digit)
{
  digit = DIGIT_TO_DECODER_VALUE[digit];
  setPin(PIN_DECODER_3, bitRead(digit, 0));
  setPin(PIN_DECODER_1, bitRead(digit, 1));
  setPin(PIN_DECODER_0, bitRead(digit, 2));
  setPin(PIN_DECODER_2, bitRead(digit, 3));
}

void setup()
{
  Serial.begin(9600);

  // настройка пинов на выход
  pinMode(PIN_DECODER_0, OUTPUT);
  pinMode(PIN_DECODER_1, OUTPUT);
  pinMode(PIN_DECODER_2, OUTPUT);
  pinMode(PIN_DECODER_3, OUTPUT);
  pinMode(PIN_HRS_L, OUTPUT);
  pinMode(PIN_HRS_R, OUTPUT);
  pinMode(PIN_MINS_L, OUTPUT);
  pinMode(PIN_MINS_R, OUTPUT);
  pinMode(PIN_GEN, OUTPUT);
  pinMode(PIN_DOT, OUTPUT);
  pinMode(PIN_BKLIGHT, OUTPUT);

  // задаем частоту ШИМ на 9 и 10 выводах 31 кГц
  TCCR1B = TCCR1B & 0b11111000 | 1; // ставим делитель 1

  // включаем ШИМ
  // от скважности зависит напряжение! у 175 вольт при значении 180 и 145 вольт при 120
  setPWM(9, DUTY_CYCLE);
  /*
  // перенастраиваем частоту ШИМ на пинах 3 и 11 на 7.8 кГц и разрешаем прерывания по совпадению
  TCCR2B = (TCCR2B & B11111000) | 2;    // делитель 8
  TCCR2A |= (1 << WGM21);   // включить CTC режим для COMPA
  TIMSK2 |= (1 << OCIE2A);  // включить прерывания по совпадению COMPA
*/
  setPWM(PIN_BKLIGHT, 1); // шим на светодиоды подсветки
  setPWM(PIN_DOT, 1);     // шим на точку (разделитель часы:минуты)
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
