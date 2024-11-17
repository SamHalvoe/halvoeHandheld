#pragma once

#include <tgx.h>
#include <FT6236.h>
#include "InputEventHandler.hpp"

namespace halvoeHandheld
{
  const uint8_t TOUCH_RESET_PIN = 3;
  const uint8_t TOUCH_SCL_PIN = 24;
  const uint8_t TOUCH_SDA_PIN = 25;
  const uint8_t TOUCH_THRESHHOLD = 32;

  class TouchHandler : public InputSource
  {
    private:
      uint8_t m_touchUpdateInterval = 25;
      elapsedMillis m_timeSinceTouchUpdated;
      FT6236 m_touchDevice;
      std::pair<tgx::iVec2, tgx::iVec2> m_touchPoints;
      std::pair<bool, bool> m_isTouched;
      std::pair<tgx::iBox2, tgx::iBox2> m_screenHalf;

    public:
      TouchHandler(std::vector<Event>& out_eventList);
      bool begin(Stream& out_loggingStreamLibraries);
      void update();
      uint8_t getTouchCount() const;
      const tgx::iVec2& getFirstTouchPoint() const;
      const tgx::iVec2& getSecondTouchPoint() const;
  };
}
