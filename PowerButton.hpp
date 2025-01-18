#pragma once

#include <Arduino.h>
#include <functional>

// ---- FUNCTION OBJECT: PowerOffRequestHandler

using PowerOffRequestHandler = std::function<bool()>;

// ---- CLASS: PowerButton

class PowerButton
{
  private:
    uint8_t m_buttonPin;
    uint8_t m_offPin;
    uint16_t m_offPressTime;
    bool m_isPressed = false;
    elapsedMillis m_timeSincePress;
    PowerOffRequestHandler m_powerOffRequestHandler;

  public:
    PowerButton(uint8_t in_buttonPin, uint8_t in_offPin, uint16_t in_offPressTime);
    void setPowerOffRequestHandler(PowerOffRequestHandler in_powerOffRequestHandler);
    void update();
};
