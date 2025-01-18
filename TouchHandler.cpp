#include "TouchHandler.hpp"
#include "DisplayDefinitions.hpp"
#include "halvoeLog.hpp"

namespace halvoeHandheld
{
  TouchHandler::TouchHandler() : m_touchDevice(Wire2)
  {
    m_touchPoints.first = { -1, -1 };
    m_touchPoints.second = { -1, -1 };
    m_screenHalf.first = { 0, (TFT_PIXEL_HEIGHT / 2) - 1, 0, TFT_PIXEL_WIDTH - 1 };
    m_screenHalf.second = { TFT_PIXEL_HEIGHT / 2, TFT_PIXEL_HEIGHT - 1, 0, TFT_PIXEL_WIDTH - 1 };
  }

  bool TouchHandler::begin(Stream& out_loggingStreamLibraries)
  {
    LOG_INFO("---- Touch Device Setup Begin ----");

    Wire2.begin();
    Wire2.setClock(400000);

    pinMode(TOUCH_RESET_PIN, OUTPUT);
    digitalWrite(TOUCH_RESET_PIN, LOW);
    delay(500);
    digitalWrite(TOUCH_RESET_PIN, HIGH);
    delay(2000);

    if (not m_touchDevice.begin(TOUCH_THRESHHOLD))
    {
      LOG_ERROR("ERROR: Could not initialise touchDevice!");
      m_touchDevice.printDebugInfo(out_loggingStreamLibraries);
    }
    m_touchDevice.printDebugInfo(out_loggingStreamLibraries);

    LOG_INFO("---- Touch Device Setup End ----");
    return true;
  }

  void TouchHandler::update()
  {
    if (m_timeSinceTouchUpdated > m_touchUpdateInterval)
    {
      m_touchDevice.readData();

      if (m_touchDevice.touches > 0)
      {
        tgx::iVec2 touchPoint0(m_touchDevice.touchY[0], TFT_PIXEL_WIDTH - m_touchDevice.touchX[0]);
        m_touchPoints.first = touchPoint0;
        m_isTouched.first = true;
        dispatchEvent({ Event::Type::pressed, 0, m_touchPoints.first });
        
        if (m_touchDevice.touches > 1)
        {
          tgx::iVec2 touchPoint1(m_touchDevice.touchY[1], TFT_PIXEL_WIDTH - m_touchDevice.touchX[1]);

          if (m_screenHalf.second.contains(touchPoint1))
          {
            m_touchPoints.second = touchPoint1;
            m_isTouched.second = true;
            dispatchEvent({ Event::Type::pressed, 1, m_touchPoints.second });
          }
        }
        else if (m_isTouched.second)
        {
          m_isTouched.second = false;
          dispatchEvent({ Event::Type::released, 1, m_touchPoints.second });
        }

        LOG_TRACE(m_touchDevice.touches, " | ",
                  m_touchDevice.touchID[0], " ", m_touchDevice.touchID[1], " ",
                  m_touchDevice.touchX[0], " ", m_touchDevice.touchX[1], " ",
                  m_touchDevice.touchY[0], " ", m_touchDevice.touchY[1], "\n",
                  "p1 ", m_touchPoints.first.x, " ", m_touchPoints.first.y, "\n",
                  "p2 ", m_touchPoints.second.x, " ", m_touchPoints.second.y, "\n");
      }
      else
      {
        if (m_isTouched.first)
        {
          m_isTouched.first = false;
          dispatchEvent({ Event::Type::released, 0, m_touchPoints.first });
        }

        if (m_isTouched.second)
        {
          m_isTouched.second = false;
          dispatchEvent({ Event::Type::released, 1, m_touchPoints.second });
        }
      }

      m_timeSinceTouchUpdated = 0;
     }
  }

  uint8_t TouchHandler::getTouchCount() const
  {
    return m_touchDevice.touches;
  }

  const tgx::iVec2& TouchHandler::getFirstTouchPoint() const
  {
    return m_touchPoints.first;
  }

  const tgx::iVec2& TouchHandler::getSecondTouchPoint() const
  {
    return m_touchPoints.second;
  }
}
