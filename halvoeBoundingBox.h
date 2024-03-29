#pragma once

class BoundingBox
{
  protected:
    int16_t m_xLeft = 0;
    int16_t m_yUp = 0;
    int16_t m_xRight = 0;
    int16_t m_yDown = 0;
    
  public:
    BoundingBox(int16_t in_x = 0, int16_t in_y = 0, int16_t in_width = 0, int16_t in_height = 0) :
      m_xLeft(in_x), m_yUp(in_y), m_xRight(in_x + in_width), m_yDown(in_y + in_height)
    {}

    void setXLeft(int16_t in_xLeft)
    {
      m_xLeft = in_xLeft;
    }

    void setXRight(int16_t in_xRight)
    {
      m_xRight = in_xRight;
    }

    void setYUp(int16_t in_yUp)
    {
      m_yUp = in_yUp;
    }

    void setYDown(int16_t in_yDown)
    {
      m_yDown = in_yDown;
    }

    int16_t getXLeft() const
    {
      return m_xLeft;
    }

    int16_t getXRight() const
    {
      return m_xRight;
    }

    int16_t getYUp() const
    {
      return m_yUp;
    }

    int16_t getYDown() const
    {
      return m_yDown;
    }

    int16_t getX() const
    {
      return getXLeft();
    }

    int16_t getY() const
    {
      return getYUp();
    }

    int16_t getWidth() const
    {
      return getXRight() - getXLeft();
    }

    int16_t getHeigth() const
    {
      return getYDown() - getYUp();
    }

    bool intersects(int16_t in_x, int16_t in_y) const
    {
      if (in_x >= m_xLeft && in_x <= m_xRight &&
          in_y >= m_yUp && in_y <= m_yDown)
      {
        return true;
      }

      return false;
    }
};
