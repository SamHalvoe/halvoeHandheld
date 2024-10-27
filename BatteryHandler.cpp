#include "BatteryHandler.hpp"

BatteryHandler::BatteryHandler(TwoWire& io_wire) : m_batteryHandler(io_wire)
{}

bool BatteryHandler::begin()
{
  m_isReady = m_batteryHandler.begin();

  if (m_isReady)
  {
    m_batteryHandler.enterConfig();
    m_batteryHandler.setCapacity(m_capacity); // set the battery capacity in mAh
    m_batteryHandler.exitConfig();
  }
  else
  {
    #if HALVOE_LOG_SERIAL_ENABLED
    Serial.println("Initialization of battery handler failed!");
    #endif // HALVOE_LOG_SERIAL_ENABLED
  }

  return m_isReady;
}

bool BatteryHandler::isReady() const
{
  return m_isReady;
}

void BatteryHandler::update()
{
  if (m_isReady && m_timeSinceUpdate >= m_updateInterval)
  {
    m_stateOfCharge = m_batteryHandler.soc();
    m_timeSinceUpdate = 0;
  }
}

uint16_t BatteryHandler::getStateOfCharge() const // in %
{
  return m_stateOfCharge;
}
