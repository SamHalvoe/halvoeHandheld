#include "PowerButton.hpp"

PowerButton::PowerButton(uint8_t in_buttonPin, uint8_t in_offPin, uint16_t in_offPressTime) :
  m_buttonPin(in_buttonPin), m_offPin(in_offPin), m_offPressTime(in_offPressTime)
{
  pinMode(m_buttonPin, INPUT_PULLUP);
  pinMode(m_offPin, OUTPUT);
  digitalWrite(m_offPin, LOW);
}

void PowerButton::setPowerOffRequestHandler(PowerOffRequestHandler in_powerOffRequestHandler)
{
  m_powerOffRequestHandler = in_powerOffRequestHandler;
}

void PowerButton::update()
{
  if (digitalRead(m_buttonPin) == LOW)
  {
    if (m_isPressed)
    {
      if (m_timeSincePress >= m_offPressTime)
      {
        if (m_powerOffRequestHandler && m_powerOffRequestHandler())
        {
          digitalWrite(m_offPin, HIGH);
        }
      }
    }
    else
    {
      m_isPressed = true;
      m_timeSincePress = 0;
    }
  }
  else
  {
    m_isPressed = false;
  }
}
