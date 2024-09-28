#pragma once

#include <pimoroniTrackball.h>

#include "halvoeLogging.h"

class TrackballHandler
{
public:
  static const uint8_t DEFAULT_I2C_ADDRESS = 0x0A;
  static const uint8_t UPDATE_INTERVAL = 50; // milli sec

private:
  elapsedMillis m_timeSinceUpdate;
  PimoroniTrackball m_trackball;

public:
  bool begin(TwoWire& io_wire, const uint8_t in_address = DEFAULT_I2C_ADDRESS)
  {
    m_trackball.begin(in_address, io_wire);
    m_trackball.setRGBW(0, 0, 0, 255);

    return true;
  }

  bool update()
  {
    bool wasChanged = false;

    if (m_timeSinceUpdate >= UPDATE_INTERVAL)
    {
      wasChanged = m_trackball.read();

      #if HALVOE_LOG_SERIAL_ENABLED && HALVOE_LOG_LEVEL_SERIAL >= 8
      if (wasChanged)
      {
        Serial.print(" ");
        Serial.println(m_trackball.up());
        Serial.print(m_trackball.left());
        Serial.print("+");
        Serial.println(m_trackball.right());
        Serial.print(" ");
        Serial.println(m_trackball.down());
      }
      #endif // HALVOE_LOG_SERIAL_ENABLED

      m_timeSinceUpdate = 0;
    }

    return wasChanged;
  }

  uint8_t up()
  {
    return m_trackball.up();
  }

  uint8_t left()
  {
    return m_trackball.left();
  }

  uint8_t right()
  {
    return m_trackball.right();
  }

  uint8_t down()
  {
    return m_trackball.down();
  }

  bool clicked()
  {
    return m_trackball.click();
  }

  bool released()
  {
    return m_trackball.release();
  }
};