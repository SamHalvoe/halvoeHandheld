#pragma once

#define DEBUGLOG_DEFAULT_LOG_LEVEL_INFO
#define DEBUGLOG_DEFAULT_FILE_LEVEL_INFO
#define DEBUGLOG_ENABLE_FILE_LOGGER

#include <SD.h> // this header is needed, because for file logging FILE_WRITE has to be defined and FS.h (included by SD.h) defines FILE_WRITE properly
#include <DebugLog.h>
#include <StreamUtils.hpp>
#include <elapsedMillis.h>

namespace halvoeHandheld
{
  class LogFileManager
  {
    private:
      const char* m_logFilePath;
      const unsigned long m_logFileFlushInterval; // in ms
      elapsedMillis m_timeSinceFlush;
      bool m_isSetup = false;

      const char* m_logFilePathLibraries;
      const unsigned long m_logFileFlushIntervalLibraries; // in ms
      elapsedMillis m_timeSinceFlushLibraries;
      File m_logFileLibraries;
      StreamUtils::LoggingStream m_logStreamLibraries;
      bool m_isSetupLibraries = false;

    public:
      LogFileManager();
      bool setup();
      bool isSetup() const;
      bool isSetupLibraries() const;
      StreamUtils::LoggingStream& getLogStreamLibraries();
      void flush();
      void flushNow();
      void flushLibraries();
      bool handleCrashReport();
  };
}
