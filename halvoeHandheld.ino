#include "DisplayHandler.h"

void setupSerial()
{
  Serial.begin(9600);

  elapsedMillis initialisationTime;
  while (not Serial && initialisationTime < 10000);

  if (Serial)
  {
    Serial.println("Serial is ready");
    Serial.println("(initialisationTime: " + String(initialisationTime) + " ms)");
  }
}

void setup()
{
  setupSerial();
  setupDisplay();
}

void loop()
{
  delay(1000);
}
