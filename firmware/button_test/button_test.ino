#include <EncButton.h>

EncButton<EB_TICK, 3> btn1;
EncButton<EB_TICK, 4> btn2;
int num = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  btn2.setStepTimeout(150);
  btn2.setHoldTimeout(200);
}

void buttonsTick()
{
  btn1.tick();
  btn2.tick();
  bool isAdjust = btn1.hold();

  if (isAdjust)
  {
    if (btn2.press())
    {
      Serial.println("Click state 2");
    }
  }
  else
  {
    if (btn2.press() || btn2.step())
    {
      num++;
      num = num % 24;
      Serial.println(String(num));
    }
  }
}

void loop()
{
  buttonsTick();
}
