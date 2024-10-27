#pragma once

#include <Adafruit_GFX.h>
#include <ILI9341_T4.h>

#include "halvoeBoundingBox.hpp"

class Label
{
  protected:
    Adafruit_GFX* m_canvas;
    String m_text;
    BoundingBox m_boundingBox;
    uint8_t m_textSizeX = 1;
    uint8_t m_textSizeY = 1;
    uint16_t m_foregroundColor = ILI9341_T4_COLOR_WHITE;
    uint16_t m_backgroundColor = ILI9341_T4_COLOR_BLACK;
    uint16_t m_outlineColor = ILI9341_T4_COLOR_BLACK;

  protected:
    void updateXRightYDown();

  public:
    Label(Adafruit_GFX* io_canvas, const String& in_text,
          int16_t in_x = 0, int16_t in_y = 0,
          uint8_t in_textSizeX = 1, uint8_t in_textSizeY = 1,
          uint16_t in_foregroundColor = ILI9341_T4_COLOR_WHITE,
          uint16_t in_backgroundColor = ILI9341_T4_COLOR_BLACK,
          uint16_t in_outlineColor = ILI9341_T4_COLOR_BLACK);
    void setText(const String& in_text);
    const String& getText() const;
    const BoundingBox& getBoundingBox() const;
    void setForegroundColor(uint16_t in_foregroundColor);
    void setBackgroundColor(uint16_t in_backgroundColor);
    void setOutlineColor(uint16_t in_outlineColor);
    void draw();
};
