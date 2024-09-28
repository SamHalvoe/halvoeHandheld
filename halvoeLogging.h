#pragma once

#include "halvoeVersion.h"

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

  void logVersion()
  {
    Serial.println("halvoeHandheld");
    Serial.println(String("build version: ") + buildVersion);
    Serial.println(String("build timestamp: ") + buildTimestamp);
  }
}