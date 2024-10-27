#include "halvoeBoundingBox.hpp"

BoundingBox::BoundingBox(int16_t in_x, int16_t in_y, int16_t in_width, int16_t in_height) :
  m_xLeft(in_x), m_yUp(in_y), m_xRight(in_x + in_width), m_yDown(in_y + in_height)
{}

void BoundingBox::setXLeft(int16_t in_xLeft)
{
  m_xLeft = in_xLeft;
}

void BoundingBox::setXRight(int16_t in_xRight)
{
  m_xRight = in_xRight;
}

void BoundingBox::setYUp(int16_t in_yUp)
{
  m_yUp = in_yUp;
}

void BoundingBox::setYDown(int16_t in_yDown)
{
  m_yDown = in_yDown;
}

int16_t BoundingBox::getXLeft() const
{
  return m_xLeft;
}

int16_t BoundingBox::getXRight() const
{
  return m_xRight;
}

int16_t BoundingBox::getYUp() const
{
  return m_yUp;
}

int16_t BoundingBox::getYDown() const
{
  return m_yDown;
}

int16_t BoundingBox::getX() const
{
  return getXLeft();
}

int16_t BoundingBox::getY() const
{
  return getYUp();
}

int16_t BoundingBox::getWidth() const
{
  return getXRight() - getXLeft();
}

int16_t BoundingBox::getHeigth() const
{
  return getYDown() - getYUp();
}

bool BoundingBox::intersects(int16_t in_x, int16_t in_y) const
{
  if (in_x >= m_xLeft && in_x <= m_xRight &&
      in_y >= m_yUp && in_y <= m_yDown)
  {
    return true;
  }

  return false;
}
