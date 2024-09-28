#pragma once

#include "halvoeVersion.h"

// 0 = disabled // 1 enabled
#define HALVOE_LOG_SERIAL_ENABLED 1
#define HALVOE_LOG_FILE_ENABLED 1

// 0 = min // 9 = max
#define HALVOE_LOG_LEVEL_SERIAL 8
#define HALVOE_LOG_LEVEL_FILE 9

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
