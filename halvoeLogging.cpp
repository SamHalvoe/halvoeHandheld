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

  constexpr const char* getVersionString()
  {
    return "halvoeHandheld\n"
           "build version: " HALVOE_BUILD_VERSION "\n"
           "build timestamp: " HALVOE_BUILD_TIMESTAMP "\n";
  }
}
