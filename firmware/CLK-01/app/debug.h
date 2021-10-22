#ifndef debug_h
#define debug_h

#if DEBUG == DEBUG_ON
void debug(String str)
{
  Serial.println(str);
}

void setupDebug()
{
  Serial.begin(9600);
}
#else
void debug(String str)
{
}

void setupDebug()
{
}
#endif

#endif
