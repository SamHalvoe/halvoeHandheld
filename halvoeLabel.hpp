#pragma once

#include <tgx.h>
#include <font_SourceCodePro_AA4_lite.h>
#include "InputEventHandler.hpp"

class Label
{
  protected:
    tgx::Image<tgx::RGB565> m_target;
    String m_text;
    uint8_t m_textSize = 14;
    tgx::iVec2 m_topLeftPoint;
    tgx::iBox2 m_boundingBox;
    tgx::RGB565 m_foregroundColor = tgx::RGB565_White;
    tgx::RGB565 m_backgroundColor = tgx::RGB565_Black;
    tgx::RGB565 m_outlineColor = tgx::RGB565_White;
    uint16_t m_eventID = Event::NO_ID;

  protected:
    void updateBoundingBox();

  public:
    Label(tgx::Image<tgx::RGB565>& io_target, const String& in_text,
          int16_t in_x = 0, int16_t in_y = 0, uint8_t in_textSize = 14,
          tgx::RGB565 in_foregroundColor = tgx::RGB565_White,
          tgx::RGB565 in_backgroundColor = tgx::RGB565_Black,
          tgx::RGB565 in_outlineColor = tgx::RGB565_White);
    void setText(const String& in_text);
    const String& getText() const;
    const tgx::iBox2& getBoundingBox() const;
    void setForegroundColor(tgx::RGB565 in_foregroundColor);
    void setBackgroundColor(tgx::RGB565 in_backgroundColor);
    void setOutlineColor(tgx::RGB565 in_outlineColor);
    void draw();

    void handleEventPressed(const Event& in_event);
    void handleEventReleased(const Event& in_event);
};
