#include "OrientationHandler.hpp"
#include "halvoeLog.hpp"

OrientationHandler::OrientationHandler()
{
  m_timeSinceSensorUpdate = 200;
}

bool OrientationHandler::setup()
{
  m_isSensorReady = m_sensor.begin_I2C();

  if (m_isSensorReady)
  {
    if (not m_sensor.enableReport(SH2_GAME_ROTATION_VECTOR))
    {
      m_isSensorReady = false;
      LOG_ERROR("enableReport(SH2_GAME_ROTATION_VECTOR) failed!");
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
      LOG_DEBUG("Game Rotation Vector - r: ", m_sensorValue.un.gameRotationVector.real,
                " i: ", m_sensorValue.un.gameRotationVector.i,
                " j: ", m_sensorValue.un.gameRotationVector.j,
                " k: ", m_sensorValue.un.gameRotationVector.k, "\n");
    break;
  }
}
