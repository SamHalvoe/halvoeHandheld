#pragma once

#include <Haptic_Driver.h>

#include "halvoeLogging.h"

namespace halvoeHandheld
{
  Haptic_Driver hapticDriver;

  bool setupHapticDriver()
  {
    if (hapticDriver.begin(Wire1))
    {
      if (hapticDriver.defaultMotor())
      {
        // Frequency tracking is done by the IC to ensure that the motor is hitting
        // its resonant frequency. I found that restricting the PCB (squeezing)
        // raises an error which stops operation because it can not reach resonance.
        // I disable here to avoid this error. 
        hapticDriver.enableFreqTrack(false);

        // set operation mode to I2C
        hapticDriver.setOperationMode(DRO_MODE);
        delay(1000);

        hapticDriver.setVibrate(127);
        delay(500);
        hapticDriver.setVibrate(0);
      }
      else
      {
        #if HALVOE_LOG_SERIAL_ENABLED
        Serial.println("Setup of haptic driver default motor failed!");
        #endif // HALVOE_LOG_SERIAL_ENABLED

        return false;
      }
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
