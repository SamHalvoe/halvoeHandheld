#pragma once

#include <Adafruit_BNO08x.h>

class OrientationHandler
{
  private:
    Adafruit_BNO08x m_sensor;
    sh2_SensorValue_t m_sensorValue;
    bool m_isSensorReady = false;
    elapsedMillis m_timeSinceSensorUpdate;

  public:
    OrientationHandler();
    bool setup();
    void update();
};
