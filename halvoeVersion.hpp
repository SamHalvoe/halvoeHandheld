#pragma once

#pragma message "Build timestamp: " __DATE__ " " __TIME__

namespace halvoeHandheld
{
  constexpr const char* buildVersion = "0.0.1";
  constexpr const char* buildTimestamp = __DATE__ " " __TIME__;
}
