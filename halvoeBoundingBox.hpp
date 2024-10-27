#pragma once

#include <cstdint>

class BoundingBox
{
  protected:
    int16_t m_xLeft = 0;
    int16_t m_yUp = 0;
    int16_t m_xRight = 0;
    int16_t m_yDown = 0;
    
  public:
    BoundingBox(int16_t in_x = 0, int16_t in_y = 0, int16_t in_width = 0, int16_t in_height = 0);
    void setXLeft(int16_t in_xLeft);
    void setXRight(int16_t in_xRight);
    void setYUp(int16_t in_yUp);
    void setYDown(int16_t in_yDown);
    int16_t getXLeft() const;
    int16_t getXRight() const;
    int16_t getYUp() const;
    int16_t getYDown() const;
    int16_t getX() const;
    int16_t getY() const;
    int16_t getWidth() const;
    int16_t getHeigth() const;
    bool intersects(int16_t in_x, int16_t in_y) const;
};
