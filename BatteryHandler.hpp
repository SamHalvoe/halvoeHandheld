#pragma once

#include <SparkFunBQ27441.h>

#include "halvoeLogging.h"

class BatteryHandler
{
  private:
    BQ27441 m_batteryHandler;
    bool m_isReady = false;
    const uint16_t m_capacity = 4000; // mAh

    const uint16_t m_updateInterval = 10000; // ms
    elapsedMillis m_timeSinceUpdate = m_updateInterval;
    uint16_t m_stateOfCharge = 0;

  public:
    BatteryHandler(TwoWire& io_wire) : m_batteryHandler(io_wire)
    {}

    bool begin()
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

    bool isReady() const
    {
      return m_isReady;
    }

    void update()
    {
      if (m_isReady && m_timeSinceUpdate >= m_updateInterval)
      {
        m_stateOfCharge = m_batteryHandler.soc();
        m_timeSinceUpdate = 0;
      }
    }

    uint16_t getStateOfCharge() const // in %
    {
      return m_stateOfCharge;
    }
};
