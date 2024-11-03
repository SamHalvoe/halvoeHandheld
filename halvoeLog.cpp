#include "halvoeLog.hpp"

namespace halvoeHandheld
{
  LogFileManager::LogFileManager() :
    m_logFilePath("/halvoeHandheld.log"),
    m_logFileFlushInterval(60 * 1000), // ms
    m_isSetup(false),
    m_logFilePathLibraries("/libraries.log"),
    m_logFileFlushIntervalLibraries(60 * 1000), // ms
    m_logStreamLibraries(m_logFileLibraries, Serial),
    m_isSetupLibraries(false)
  {}

  bool LogFileManager::setup()
  {
    LOG_ATTACH_FS_MANUAL(SD, m_logFilePath, FILE_WRITE);
    m_isSetup = LOG_FILE_IS_OPEN();

    if (m_isSetup)
    {
      LOG_INFO("[Log file is ready]");
    }
    else
    {
      LOG_ERROR("Failed to setup log file!");
    }

    m_logFileLibraries = SD.open(m_logFilePathLibraries, FILE_WRITE);

    if (m_logFileLibraries)
    {
      m_logStreamLibraries.println("[Log file for libraries is ready]");
      LOG_INFO("[Log file for libraries is ready]");
      m_isSetupLibraries = true;
    }
    else
    {
      LOG_ERROR("Failed to setup log file for libraries!");
    }

    return m_isSetup && m_isSetupLibraries;
  }

  bool LogFileManager::isSetup() const
  {
    return m_isSetup;
  }

  bool LogFileManager::isSetupLibraries() const
  {
    return m_isSetupLibraries;
  }

  StreamUtils::LoggingStream& LogFileManager::getLogStreamLibraries()
  {
    return m_logStreamLibraries;
  }

  void LogFileManager::flush()
  {
    if (m_timeSinceFlush >= m_logFileFlushInterval)
    {
      LOG_FILE_FLUSH();
      LOG_INFO("LOG_FILE_FLUSHed");
      m_timeSinceFlush = 0;
    }
  }

  void LogFileManager::flushNow()
  {
    LOG_FILE_FLUSH();
    LOG_INFO("LOG_FILE_FLUSHed");
  }

  void LogFileManager::flushLibraries()
  {
    if (m_timeSinceFlushLibraries >= m_logFileFlushIntervalLibraries)
    {
      m_logStreamLibraries.flush();
      LOG_INFO("Audio library log file flushed");
      m_timeSinceFlushLibraries = 0;
    }
  }
}
