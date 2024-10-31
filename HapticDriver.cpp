#include "HapticDriver.hpp"
#include "halvoeLog.hpp"

HapticDriver::HapticDriver()
{}

bool HapticDriver::setup()
{
  if (m_driver.begin(&Wire1))
  {
    m_driver.selectLibrary(1);

    // I2C trigger by sending 'go' command 
    // default, internal trigger when sending GO command
    m_driver.setMode(DRV2605_MODE_INTTRIG);

    // set the effect to play
    m_driver.setWaveform(0, 118);  // set effect to play "Long buzz for programmatic stopping – 100%"
    m_driver.setWaveform(1, 0);    // end waveform

    /*m_driver.go();
    delay(100);
    m_driver.stop();*/
  }
  else
  {
    LOG_ERROR("Initialization of haptic driver failed!");
    return false;
  }

  return true;
}


Adafruit_DRV2605& HapticDriver::getDriver()
{
  return m_driver;
}
