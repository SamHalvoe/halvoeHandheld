#pragma once

#include <SparkFunBQ27441.h>

#include "halvoeLogging.hpp"

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
    BatteryHandler(TwoWire& io_wire);
    bool begin();
    bool isReady() const;
    void update();
    uint16_t getStateOfCharge() const; // in %
};
