#include "halvoeLogging.hpp"
#include <Arduino.h>

namespace halvoeHandheld
{
  void setupSerial()
  {
    Serial.begin(115200);

    elapsedMillis initialisationTime;
    while (not Serial && initialisationTime < 10000);

    if (Serial)
    {
      Serial.println();
      Serial.print("Serial is ready ");
      Serial.println("(initialisationTime: " + String(initialisationTime) + " ms)");
    }
  }
}
