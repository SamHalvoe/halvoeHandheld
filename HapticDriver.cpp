#include "HapticDriver.hpp"
#include "halvoeLog.hpp"

HapticDriver::HapticDriver()
{}

bool HapticDriver::setup()
{
  if (m_driver.begin(&Wire1))
  {
    m_driver.useLRA();
    m_driver.setMode(DRV2605_MODE_REALTIME);
    m_driver.writeRegister8(DRV2605_REG_CONTROL3, m_driver.readRegister8(DRV2605_REG_CONTROL3) | 0x08); // set DATA_FORMAT_RTP to unsigned (0-255)
    
    /*LOG_INFO("m_driver.setRealtimeValue(255)");
    m_driver.setRealtimeValue(255);
    delay(3000);
    m_driver.setRealtimeValue(0);
    LOG_INFO("m_driver.setRealtimeValue(0)");*/
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
