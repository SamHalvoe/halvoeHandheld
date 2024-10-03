#pragma once

#include <Adafruit_BNO08x.h>

namespace halvoeHandheld
{
  Adafruit_BNO08x bno08x;
  sh2_SensorValue_t bno08xSensorValue;
  bool isBno08xReady = false;
  elapsedMillis bno08xTimeSinceUpdate;

  bool setupOrientationHandler()
  {
    isBno08xReady = bno08x.begin_I2C();

    if (isBno08xReady)
    {
      Serial.println("begin_I2C = true");
      if (not bno08x.enableReport(SH2_GAME_ROTATION_VECTOR))
      {
        isBno08xReady = false;
        Serial.println("enableReport = false");
      }
    }

    return isBno08xReady;
  }

  void updateOrientationHandler()
  {
    if (not isBno08xReady) { return; }
    if (bno08xTimeSinceUpdate < 200) { return; } else { bno08xTimeSinceUpdate = 0; }
    if (not bno08x.getSensorEvent(&bno08xSensorValue)) { return; }

    switch (bno08xSensorValue.sensorId)
    {
      case SH2_GAME_ROTATION_VECTOR:
        #if HALVOE_LOG_SERIAL_ENABLED && HALVOE_LOG_LEVEL_SERIAL > 8
        Serial.print("Game Rotation Vector - r: ");
        Serial.print(bno08xSensorValue.un.gameRotationVector.real);
        Serial.print(" i: ");
        Serial.print(bno08xSensorValue.un.gameRotationVector.i);
        Serial.print(" j: ");
        Serial.print(bno08xSensorValue.un.gameRotationVector.j);
        Serial.print(" k: ");
        Serial.println(bno08xSensorValue.un.gameRotationVector.k);
        #endif // HALVOE_LOG_SERIAL_ENABLED
      break;
    }
  }
}
