#pragma once

#include <SD.h>

#include "halvoeVersion.h"

class Logger
{
  public:
    enum LogTarget : uint8_t
    {
      LT_SERIAL = 0,
      LT_FILE,
      LT_SERIAL_AND_FILE
    };

    enum LogResult : uint8_t
    {
      LR_SUCCESS = 0,
      LR_TO_SERIAL_FAILED = 1,
      LR_TO_FILE_FAILED = 2,
      LR_TO_SERIAL_AND_FILE_FAILED = 3
    };

    static const size_t DEFAULT_FILE_BUFFER_SIZE = 256;
    static const size_t DEFAULT_SERIAL_BAUDRATE = 115200;

  private:
    File m_file;

  private:
    void printToSerial(const char* in_zeroTerminatedString)
    {
      if (Serial)
      {
        Serial.print(in_zeroTerminatedString);
      }
    }

    void printlnToSerial(const char* in_zeroTerminatedString)
    {
      if (Serial)
      {
        Serial.println(in_zeroTerminatedString);
      }
    }

    void printToFile(const char* in_zeroTerminatedString)
    {
      if (m_file)
      {
        m_file.print(in_zeroTerminatedString);
      }
    }

    void printlnToFile(const char* in_zeroTerminatedString)
    {
      if (m_file)
      {
        m_file.println(in_zeroTerminatedString);
      }
    }

  public:
    void setupSerial(size_t in_serialBaudrate = DEFAULT_SERIAL_BAUDRATE)
    {
      Serial.begin(in_serialBaudrate);

      elapsedMillis initialisationTime;
      while (not Serial && initialisationTime < 10000);

      if (Serial)
      {
        Serial.println();
        Serial.println("Serial logging is ready (initialisationTime: " + String(initialisationTime) + " ms)");
      }
    }

    void setupFile(const char* in_fileName = "main.log")
    {
      String path("/");
      path.append(in_fileName);

      m_file = SD.open(path.c_str(), FILE_WRITE);

      println("File logging is ready");
    }

    void print(const char* in_zeroTerminatedString, LogTarget in_logTarget = LT_SERIAL_AND_FILE)
    {
      switch (in_logTarget)
      {
        case LT_SERIAL:
          printToSerial(in_zeroTerminatedString);
        break;
        
        case LT_FILE:
          printToFile(in_zeroTerminatedString);
        break;

        case LT_SERIAL_AND_FILE:
          printToSerial(in_zeroTerminatedString);
          printToFile(in_zeroTerminatedString);
        break;
      }
    }

    void println(const char* in_zeroTerminatedString, LogTarget in_logTarget = LT_SERIAL_AND_FILE)
    {
      switch (in_logTarget)
      {
        case LT_SERIAL:
          printlnToSerial(in_zeroTerminatedString);
        break;
        
        case LT_FILE:
          printlnToFile(in_zeroTerminatedString);
        break;

        case LT_SERIAL_AND_FILE:
          printlnToSerial(in_zeroTerminatedString);
          printlnToFile(in_zeroTerminatedString);
        break;
      }
    }

    void print(const String& in_arduinoString, LogTarget in_logTarget = LT_SERIAL_AND_FILE)
    {
      print(in_arduinoString.c_str(), in_logTarget);
    }

    void println(const String& in_arduinoString, LogTarget in_logTarget = LT_SERIAL_AND_FILE)
    {
      println(in_arduinoString.c_str(), in_logTarget);
    }

    void flushFile()
    {
      if (m_file)
      {
        m_file.flush();
      }
    }

    void printVersion()
    {
      println("+------------------------------------------------+");
      println("halvoeHandheld");
      println(String("build version: ") + halvoeHandheld::buildVersion);
      println(String("build timestamp: ") + halvoeHandheld::buildTimestamp);
      println("+------------------------------------------------+");
    }
};

namespace halvoeHandheld
{
  Logger logger;
}
