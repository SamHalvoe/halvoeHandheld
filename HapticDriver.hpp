#pragma once

#include <Adafruit_DRV2605.h>
#include "halvoeLogging.hpp"

class HapticDriver
{
  private:
    Adafruit_DRV2605 m_driver;

  public:
    HapticDriver();
    bool setup();
    Adafruit_DRV2605& getDriver();
};
