const byte CATHOD_TO_DIGIT[] = {1, 6, 2, 7, 5, 0, 4, 9, 8, 3};
boolean flipInit;
bool trainLeaving;
byte startCathode[4], endCathode[4];
byte currentLamp, flipEffectStages;
boolean flipIndics[4];
boolean indiBrightDirection;

void flipTick()
{
  if (currentEffectsMode == EFFECT_NONE)
  {
    sendTime(hrs, mins);
    timeJustChanged = false;
  }
  else if (currentEffectsMode == EFFECT_DECAY)
  {
    if (!flipInit)
    {
      flipInit = true;
      // запоминаем, какие цифры поменялись и будем менять их яркость
      for (byte i = 0; i < 4; i++)
      {
        if (indicatorDigits[i] != newTime[i])
          flipIndics[i] = true;
        else
          flipIndics[i] = false;
      }
    }
    if (flipTimer.isReady())
    {
      if (!indiBrightDirection)
      {
        indiBrightCounter--; // уменьшаем яркость
        if (indiBrightCounter <= 0)
        {                             // если яркость меньше нуля
          indiBrightDirection = true; // меняем направление изменения
          indiBrightCounter = 0;      // обнуляем яркость
          sendTime(hrs, mins);        // меняем цифры
        }
      }
      else
      {
        indiBrightCounter++; // увеличиваем яркость
        if (indiBrightCounter >= indicatorMaxBrightness)
        {                                             // достигли предела
          indiBrightDirection = false;                // меняем направление
          indiBrightCounter = indicatorMaxBrightness; // устанавливаем максимум
          // выходим из цикла изменения
          flipInit = false;
          timeJustChanged = false;
        }
      }
      for (byte i = 0; i < 4; i++)
      {
        if (flipIndics[i])
        {
          indicatorBrightness[i] = indiBrightCounter; // применяем яркость
        }
      }
    }
  }
  else if (currentEffectsMode == EFFECT_LOOP_D)
  {
    if (!flipInit)
    {
      flipInit = true;
      // запоминаем, какие цифры поменялись и будем менять их
      for (byte i = 0; i < 4; i++)
      {
        if (indicatorDigits[i] != newTime[i])
        {
          flipIndics[i] = true;
        }
        else
        {
          flipIndics[i] = false;
        }
      }
    }

    if (flipTimer.isReady())
    {
      byte flipCounter = 0;
      for (byte i = 0; i < 4; i++)
      {
        if (flipIndics[i])
        {
          indicatorDigits[i]--;
          if (indicatorDigits[i] < 0)
          {
            indicatorDigits[i] = 9;
          }
          if (indicatorDigits[i] == newTime[i])
          {
            flipIndics[i] = false;
          }
        }
        else
        {
          flipCounter++; // счётчик цифр, которые не надо менять
        }
      }
      if (flipCounter == 4)
      { // если ни одну из 4 цифр менять не нужно
        // выходим из цикла изменения
        flipInit = false;
        timeJustChanged = false;
      }
    }
  }
  else if (currentEffectsMode == EFFECT_LOOP_C)
  {
    if (!flipInit)
    {
      flipInit = true;
      // запоминаем, какие цифры поменялись и будем менять их
      for (byte i = 0; i < 4; i++)
      {
        if (indicatorDigits[i] != newTime[i])
        {
          flipIndics[i] = true;
          for (byte c = 0; c < 10; c++)
          {
            if (indicatorDigits[i] == CATHOD_TO_DIGIT[c])
            {
              startCathode[i] = c;
            }
            if (newTime[i] == CATHOD_TO_DIGIT[c])
            {
              endCathode[i] = c;
            }
          }
        }
        else
        {
          flipIndics[i] = false;
        }
      }
    }

    if (flipTimer.isReady())
    {
      byte flipCounter = 0;
      for (byte i = 0; i < 4; i++)
      {
        if (flipIndics[i])
        {
          if (startCathode[i] > endCathode[i])
          {
            startCathode[i]--;
            indicatorDigits[i] = CATHOD_TO_DIGIT[startCathode[i]];
          }
          else if (startCathode[i] < endCathode[i])
          {
            startCathode[i]++;
            indicatorDigits[i] = CATHOD_TO_DIGIT[startCathode[i]];
          }
          else
          {
            flipIndics[i] = false;
          }
        }
        else
        {
          flipCounter++;
        }
      }
      if (flipCounter == 4)
      { // если ни одну из 4 цифр менять не нужно
        // выходим из цикла изменения
        flipInit = false;
        timeJustChanged = false;
      }
    }
  }
  else if (currentEffectsMode == EFFECT_TRAIN)
  {
    if (!flipInit)
    {
      flipInit = true;
      currentLamp = 0;
      trainLeaving = true;
      flipTimer.reset();
    }
    if (flipTimer.isReady())
    {
      if (trainLeaving)
      {
        for (byte i = 3; i > currentLamp; i--)
        {
          indicatorDigits[i] = indicatorDigits[i - 1];
        }
        anodeStates[currentLamp] = 0;
        currentLamp++;
        if (currentLamp >= 4)
        {
          trainLeaving = false; //coming
          currentLamp = 0;
          //sendTime(hrs, mins);
        }
      }
      else
      { //trainLeaving == false
        for (byte i = currentLamp; i > 0; i--)
        {
          indicatorDigits[i] = indicatorDigits[i - 1];
        }
        indicatorDigits[0] = newTime[3 - currentLamp];
        anodeStates[currentLamp] = 1;
        currentLamp++;
        if (currentLamp >= 4)
        {
          flipInit = false;
          timeJustChanged = false;
        }
      }
    }
  }

  else if (currentEffectsMode == EFFECT_RUBBER)
  {
    if (!flipInit)
    {
      flipInit = true;
      flipEffectStages = 0;
      flipTimer.reset();
    }
    if (flipTimer.isReady())
    {
      switch (flipEffectStages++)
      {
      case 1:
        anodeStates[3] = 0;
        break;
      case 2:
        anodeStates[2] = 0;
        indicatorDigits[3] = indicatorDigits[2];
        anodeStates[3] = 1;
        break;
      case 3:
        anodeStates[3] = 0;
        break;
      case 4:
        anodeStates[1] = 0;
        indicatorDigits[2] = indicatorDigits[1];
        anodeStates[2] = 1;
        break;
      case 5:
        anodeStates[2] = 0;
        indicatorDigits[3] = indicatorDigits[1];
        anodeStates[3] = 1;
        break;
      case 6:
        anodeStates[3] = 0;
        break;
      case 7:
        anodeStates[0] = 0;
        indicatorDigits[1] = indicatorDigits[0];
        anodeStates[1] = 1;
        break;
      case 8:
        anodeStates[1] = 0;
        indicatorDigits[2] = indicatorDigits[0];
        anodeStates[2] = 1;
        break;
      case 9:
        anodeStates[2] = 0;
        indicatorDigits[3] = indicatorDigits[0];
        anodeStates[3] = 1;
        break;
      case 10:
        anodeStates[3] = 0;
        //sendTime(hrs,mins);
        break;
      case 11:
        indicatorDigits[0] = newTime[3];
        anodeStates[0] = 1;
        break;
      case 12:
        anodeStates[0] = 0;
        indicatorDigits[1] = newTime[3];
        anodeStates[1] = 1;
        break;
      case 13:
        anodeStates[1] = 0;
        indicatorDigits[2] = newTime[3];
        anodeStates[2] = 1;
        break;
      case 14:
        anodeStates[2] = 0;
        indicatorDigits[3] = newTime[3];
        anodeStates[3] = 1;
        break;
      case 15:
        indicatorDigits[0] = newTime[2];
        anodeStates[0] = 1;
        break;
      case 16:
        anodeStates[0] = 0;
        indicatorDigits[1] = newTime[2];
        anodeStates[1] = 1;
        break;
      case 17:
        anodeStates[1] = 0;
        indicatorDigits[2] = newTime[2];
        anodeStates[2] = 1;
        break;
      case 18:
        indicatorDigits[0] = newTime[1];
        anodeStates[0] = 1;
        break;
      case 19:
        anodeStates[0] = 0;
        indicatorDigits[1] = newTime[1];
        anodeStates[1] = 1;
        break;
      case 20:
        indicatorDigits[0] = newTime[0];
        anodeStates[0] = 1;
        break;
      case 21:
        flipInit = false;
        timeJustChanged = false;
      }
    }
  }
}
