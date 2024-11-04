#pragma once

#include <SD.h>

namespace halvoeHandheld
{
  class SDHandler
  {
    private:
      bool m_isSetup = false;

    public:
      SDHandler();
      bool setup(uint8_t in_maxRetryCount = 3);
      bool isSetup() const;
  };
}
