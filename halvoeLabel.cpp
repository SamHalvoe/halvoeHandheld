#include "halvoeLabel.hpp"

Label::Label(tgx::Image<tgx::RGB565>& io_target, const String& in_text,
             int16_t in_x, int16_t in_y, uint8_t in_textSize,
             tgx::RGB565 in_foregroundColor, tgx::RGB565 in_backgroundColor, tgx::RGB565 in_outlineColor) :
  m_target(io_target), m_text(in_text), m_textSize(in_textSize),
  m_topLeftPoint(in_x, in_y),
  m_foregroundColor(in_foregroundColor),
  m_backgroundColor(in_backgroundColor),
  m_outlineColor(in_outlineColor)
{
  updateBoundingBox();
}

void Label::updateBoundingBox()
{
  m_boundingBox = m_target.measureText(m_text.c_str(), m_topLeftPoint, font_SourceCodePro_AA4_lite_14, tgx::Anchor::CENTER, false, false);
  m_boundingBox.minX = m_boundingBox.minX - 2;
  m_boundingBox.maxX = m_boundingBox.maxX + 2;
  m_boundingBox.minY = m_boundingBox.minY - 3;
  m_boundingBox.maxY = m_boundingBox.maxY + 3;
}

void Label::setText(const String& in_text)
{
  m_text = in_text;
  updateBoundingBox();
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
  m_target.drawTextEx(m_text.c_str(), m_topLeftPoint, font_SourceCodePro_AA4_lite_14, tgx::Anchor::CENTER, false, false, m_foregroundColor);
}

void Label::handleEventPressed(const Event& in_event)
{
  if (getBoundingBox().contains(std::get<tgx::iVec2>(in_event.m_data)))
  {
    m_eventID = in_event.m_id;
    setOutlineColor(tgx::RGB565_Red);
  }
}

void Label::handleEventReleased(const Event& in_event)
{
  if (m_eventID == in_event.m_id)
  {
    m_eventID = Event::NO_ID;
    setOutlineColor(tgx::RGB565_White);
  }
}
