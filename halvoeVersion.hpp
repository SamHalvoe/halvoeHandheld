#pragma once

#define HALVOE_BUILD_VERSION "0.0.1"
#define HALVOE_BUILD_TIMESTAMP __DATE__ " " __TIME__

#pragma message "Build timestamp: " HALVOE_BUILD_TIMESTAMP

namespace halvoeHandheld
{
  constexpr const char* buildVersion = HALVOE_BUILD_VERSION;
  constexpr const char* buildTimestamp = HALVOE_BUILD_TIMESTAMP;
}
