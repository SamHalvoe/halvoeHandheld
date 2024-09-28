#pragma once

#include <pimoroniTrackball.h>

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

      m_timeSinceUpdate = 0;
    }

    return wasChanged;
  }
};