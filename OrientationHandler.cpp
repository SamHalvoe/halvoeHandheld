#include "OrientationHandler.hpp"

OrientationHandler::OrientationHandler()
{
  m_timeSinceSensorUpdate = 200;
}

bool OrientationHandler::setup()
{
  m_isSensorReady = m_sensor.begin_I2C();

  if (m_isSensorReady)
  {
    Serial.println("begin_I2C = true");
    if (not m_sensor.enableReport(SH2_GAME_ROTATION_VECTOR))
    {
      m_isSensorReady = false;
      Serial.println("enableReport = false");
    }
  }

  return m_isSensorReady;
}

void OrientationHandler::update()
{
  if (not m_isSensorReady) { return; }
  if (m_timeSinceSensorUpdate < 200) { return; } else { m_timeSinceSensorUpdate = 0; }
  if (not m_sensor.getSensorEvent(&m_sensorValue)) { return; }

  switch (m_sensorValue.sensorId)
  {
    case SH2_GAME_ROTATION_VECTOR:
      #if HALVOE_LOG_SERIAL_ENABLED && HALVOE_LOG_LEVEL_SERIAL > 8
      Serial.print("Game Rotation Vector - r: ");
      Serial.print(m_sensorValue.un.gameRotationVector.real);
      Serial.print(" i: ");
      Serial.print(m_sensorValue.un.gameRotationVector.i);
      Serial.print(" j: ");
      Serial.print(m_sensorValue.un.gameRotationVector.j);
      Serial.print(" k: ");
      Serial.println(m_sensorValue.un.gameRotationVector.k);
      #endif // HALVOE_LOG_SERIAL_ENABLED
    break;
  }
}
