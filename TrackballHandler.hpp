#pragma once

#include <pimoroniTrackball.h>

class TrackballHandler
{
  public:
    static const uint8_t DEFAULT_I2C_ADDRESS = 0x0A;
    static const uint8_t UPDATE_INTERVAL = 25; // ms

  private:
    elapsedMillis m_timeSinceUpdate;
    PimoroniTrackball m_trackball;

  public:
    TrackballHandler();
    bool begin(TwoWire& io_wire, const uint8_t in_address = DEFAULT_I2C_ADDRESS);
    bool update();
    uint8_t up();
    uint8_t left();
    uint8_t right();
    uint8_t down();
    bool clicked();
    bool released();
};
