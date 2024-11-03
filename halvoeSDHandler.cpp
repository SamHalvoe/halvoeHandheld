#include "halvoeSDHandler.hpp"
#include "halvoeLog.hpp"

namespace halvoeHandheld
{
  SDHandler::SDHandler()
  {}

  bool SDHandler::setup()
  {
    m_isSetup = SD.begin(BUILTIN_SDCARD);
    if (not m_isSetup) { LOG_ERROR("SD.begin() failed!"); }
    return m_isSetup;
  }

  bool SDHandler::isSetup() const
  {
    return m_isSetup;
  }
}
