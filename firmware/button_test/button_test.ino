#include <GyverButton.h>

GButton btn1(3, HIGH_PULL, NORM_OPEN);
GButton btn2(4, HIGH_PULL, NORM_OPEN);
int num = 0;

void setup()
{
  Serial.begin(9600);

  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  btn2.setStepTimeout(150);
  btn2.setTimeout(200);
}

void buttonsTick()
{
  btn1.tick();
  btn2.tick();
  bool isAdjust = btn1.isHold();

  if (isAdjust)
  {
    if (btn2.isPress())
    {
      Serial.println("Click state 2");
    }
  }
  else
  {
    if (btn2.isPress() || btn2.isStep())
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
