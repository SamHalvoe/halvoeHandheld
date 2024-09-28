#pragma once

#define HALVOE_BUILD_TIMESTAMP __DATE__ " " __TIME__

#pragma message "Build timestamp: " HALVOE_BUILD_TIMESTAMP

namespace halvoeHandheld
{
  constexpr const char* buildVersion = "0.0.1";
  constexpr const char* buildTimestamp = HALVOE_BUILD_TIMESTAMP;
}
