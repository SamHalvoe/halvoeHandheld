#include "halvoeLabel.hpp"

Label::Label(tgx::Image<tgx::RGB565>& io_target, const String& in_text,
             int16_t in_x, int16_t in_y, uint8_t in_textSize,
             tgx::RGB565 in_foregroundColor, tgx::RGB565 in_backgroundColor, tgx::RGB565 in_outlineColor) :
  m_target(io_target), m_text(in_text), m_textSize(in_textSize),
  m_boundingBox(in_x, in_y, in_x, in_y),
  m_foregroundColor(in_foregroundColor),
  m_backgroundColor(in_backgroundColor),
  m_outlineColor(in_outlineColor)
{
  m_boundingBox = m_target.measureText(m_text.c_str(), { m_boundingBox.minX, m_boundingBox.minY }, font_SourceCodePro_AA4_lite_14);
}

void Label::setText(const String& in_text)
{
  m_text = in_text;
  m_boundingBox = m_target.measureText(m_text.c_str(), { m_boundingBox.minX, m_boundingBox.minY }, font_SourceCodePro_AA4_lite_14);
}

const String& Label::getText() const
{
  return m_text;
}

const tgx::iBox2& Label::getBoundingBox() const
{
  return m_boundingBox;
}

void Label::setForegroundColor(tgx::RGB565 in_foregroundColor)
{
  m_foregroundColor = in_foregroundColor;
}

void Label::setBackgroundColor(tgx::RGB565 in_backgroundColor)
{
  m_backgroundColor = in_backgroundColor;
}

void Label::setOutlineColor(tgx::RGB565 in_outlineColor)
{
  m_outlineColor = in_outlineColor;
}

void Label::draw()
{
  m_target.fillRect(m_boundingBox, m_backgroundColor);
  m_target.drawRect(m_boundingBox, m_outlineColor);
  m_target.drawText(m_text.c_str(), { m_boundingBox.minX, m_boundingBox.minY }, font_SourceCodePro_AA4_lite_14, m_foregroundColor);
}
