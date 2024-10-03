#pragma once

#include <Adafruit_DRV2605.h>

#include "halvoeLogging.h"

namespace halvoeHandheld
{
  Adafruit_DRV2605 hapticDriver;

  bool setupHapticDriver()
  {
    if (hapticDriver.begin(&Wire1))
    {
      hapticDriver.selectLibrary(1);

      // I2C trigger by sending 'go' command 
      // default, internal trigger when sending GO command
      hapticDriver.setMode(DRV2605_MODE_INTTRIG);
      
      // set the effect to play
      hapticDriver.setWaveform(0, 118);  // set effect to play "Long buzz for programmatic stopping – 100%"
      hapticDriver.setWaveform(1, 0);    // end waveform

      /*hapticDriver.go();
      delay(100);
      hapticDriver.stop();*/
    }
    else
    {
      #if HALVOE_LOG_SERIAL_ENABLED
      Serial.println("Initialization of haptic driver failed!");
      #endif // HALVOE_LOG_SERIAL_ENABLED

      return false;
    }

    return true;
  }
}
