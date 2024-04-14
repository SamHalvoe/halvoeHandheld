#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#include "halvoeBoundingBox.h"

class Label
{
  protected:
    Adafruit_GFX* m_canvas;
    String m_text;
    BoundingBox m_boundingBox;
    uint8_t m_textSizeX = 1;
    uint8_t m_textSizeY = 1;
    uint16_t m_foregroundColor = ILI9341_WHITE;
    uint16_t m_backgroundColor = ILI9341_BLACK;
    uint16_t m_outlineColor = ILI9341_BLACK;

  protected:
    void updateXRightYDown()
    {
      int16_t x = 0;
      int16_t y = 0;
      uint16_t width = 0;
      uint16_t height = 0;

      m_canvas->setTextSize(m_textSizeX, m_textSizeY);
      m_canvas->getTextBounds(m_text, m_boundingBox.getXLeft(), m_boundingBox.getYUp(), &x, &y, &width, &height);

      m_boundingBox.setXRight(m_boundingBox.getXLeft() + width);
      m_boundingBox.setYDown(m_boundingBox.getYUp() + height);
    }

  public:
    Label(Adafruit_GFX* io_canvas, const String& in_text,
          int16_t in_x = 0, int16_t in_y = 0,
          uint8_t in_textSizeX = 1, uint8_t in_textSizeY = 1,
          uint16_t in_foregroundColor = ILI9341_WHITE,
          uint16_t in_backgroundColor = ILI9341_BLACK,
          uint16_t in_outlineColor = ILI9341_BLACK) :
      m_canvas(io_canvas), m_text(in_text),
      m_textSizeX(in_textSizeX), m_textSizeY(in_textSizeY),
      m_foregroundColor(in_foregroundColor),
      m_backgroundColor(in_backgroundColor),
      m_outlineColor(in_outlineColor)
    {
      m_boundingBox.setXLeft(in_x);
      m_boundingBox.setYUp(in_y);
      updateXRightYDown();
    }

    void setText(const String& in_text)
    {
      m_text = in_text;
      updateXRightYDown();
    }

    const String& getText() const
    {
      return m_text;
    }

    const BoundingBox& getBoundingBox() const
    {
      return m_boundingBox;
    }

    void setForegroundColor(uint16_t in_foregroundColor)
    {
      m_foregroundColor = in_foregroundColor;
    }

    void setBackgroundColor(uint16_t in_backgroundColor)
    {
      m_backgroundColor = in_backgroundColor;
    }

    void setOutlineColor(uint16_t in_outlineColor)
    {
      m_outlineColor = in_outlineColor;
    }

    void draw()
    {
      m_canvas->drawRect(m_boundingBox.getXLeft() + 1, m_boundingBox.getYUp() + 1,
                         m_boundingBox.getXRight() - m_boundingBox.getXLeft(),
                         m_boundingBox.getYDown() - m_boundingBox.getYUp(),
                         m_backgroundColor);
      m_canvas->setTextSize(m_textSizeX, m_textSizeY);
      m_canvas->setTextColor(m_foregroundColor, m_backgroundColor);
      m_canvas->setCursor(m_boundingBox.getXLeft() + 2, m_boundingBox.getYUp() + 2);
      m_canvas->print(m_text);
      m_canvas->drawRect(m_boundingBox.getXLeft(), m_boundingBox.getYUp(),
                         m_boundingBox.getXRight() + 2 - m_boundingBox.getXLeft(),
                         m_boundingBox.getYDown() + 2 - m_boundingBox.getYUp(),
                         m_outlineColor);
      m_canvas->drawRect(m_boundingBox.getXLeft() - 1, m_boundingBox.getYUp() - 1,
                         m_boundingBox.getXRight() + 3 - m_boundingBox.getXLeft(),
                         m_boundingBox.getYDown() + 3 - m_boundingBox.getYUp(),
                         m_outlineColor);
    }
};
