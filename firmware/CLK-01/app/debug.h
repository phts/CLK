#ifndef debug_h
#define debug_h

#define DEBUG_OFF 0
#define DEBUG_ON 1

#if DEBUG == DEBUG_ON
void debug(String str)
{
  Serial.println(str);
}

void setupDebug()
{
  Serial.begin(9600);
  Serial.println("PHTS CLK-01");
  Serial.println("Uploaded: " __DATE__ " " __TIME__);
  Serial.println("Version: " VERSION);
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
