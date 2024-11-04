#include "halvoeSDHandler.hpp"
#include "halvoeLog.hpp"

namespace halvoeHandheld
{
  SDHandler::SDHandler()
  {}

  bool SDHandler::setup(uint8_t in_maxRetryCount)
  {
    m_isSetup = SD.begin(BUILTIN_SDCARD);

    for (uint8_t retryCount = 0; not m_isSetup && retryCount < in_maxRetryCount; ++retryCount)
    {
      LOG_WARN("SD.begin() failed! Retry in 2 seconds...");
      delay(2000);
      m_isSetup = SD.begin(BUILTIN_SDCARD);
    }

    if (m_isSetup)
    {
      LOG_INFO("SD.begin() succeded!");
    }
    else
    {
      LOG_ERROR("SD.begin() failed!");
    }
    
    return m_isSetup;
  }

  bool SDHandler::isSetup() const
  {
    return m_isSetup;
  }
}
