#include <GyverButton.h>

GButton btn1(3, HIGH_PULL, NORM_OPEN);
GButton btn2(4, HIGH_PULL, NORM_OPEN);

void setup()
{
  Serial.begin(9600);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void buttonsTick()
{
  btn1.tick();
  btn2.tick();

  if (btn1.isHold())
  {
    if (btn2.isClick())
    {
      Serial.println("Click state 2");
    }
  }
  else
  {
    if (btn2.isClick())
    {
      Serial.println("Click state 1");
    }
  }
}

void loop()
{
  buttonsTick();
}
