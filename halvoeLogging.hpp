#pragma once

#include "halvoeVersion.hpp"

// 0 = disabled // 1 enabled
#define HALVOE_LOG_SERIAL_ENABLED 1
#define HALVOE_LOG_FILE_ENABLED 1

// 0 = min // 9 = max
#define HALVOE_LOG_LEVEL_SERIAL 8
#define HALVOE_LOG_LEVEL_FILE 9

namespace halvoeHandheld
{
  void setupSerial();
  constexpr const char* getVersionString();
}
