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
      bool setup();
      bool isSetup() const;
  };
}
