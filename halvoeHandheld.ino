#include "halvoeLogging.h"
#include "BatteryHandler.hpp"
#include "TrackballHandler.hpp"
#include "HapticDriver.hpp"
#include "OrientationHandler.hpp"
#include "DisplayHandler.h"
#include "halvoeLabel.h"

#include <BasicSerializer.hpp>

DisplayHandler displayHandler;
Label label(&displayHandler.getFrameCanvas(), "Test", 64, 64);
TrackballHandler trackballHandler0;
TrackballHandler trackballHandler1;
BatteryHandler batteryHandler(Wire1);

std::array<uint8_t, 128> serializerBuffer;

void setup()
{
  #if HALVOE_LOG_SERIAL_ENABLED
  halvoeHandheld::setupSerial();
  Serial.print(halvoeHandheld::getVersionString());
  #endif // HALVOE_LOG_SERIAL_ENABLED

  Serial3.begin(19200);

  displayHandler.begin();

  Wire.begin();
  Wire1.begin();

  batteryHandler.begin();
  halvoeHandheld::setupHapticDriver();
  halvoeHandheld::setupOrientationHandler();

  trackballHandler0.begin(Wire);
  trackballHandler1.begin(Wire1);
}

void loop()
{
  trackballHandler0.update();
  trackballHandler1.update();
  batteryHandler.update();

  if (trackballHandler1.clicked())
  {
    Serial.println("trackballHandler1 event");
    halvoe::Serializer<128> serializer(serializerBuffer);
    auto commandLength = serializer.skip<uint16_t>();
    serializer.write<uint16_t>(42);
    commandLength.write(serializer.getBytesWritten() - sizeof(uint16_t));
    Serial3.write(serializerBuffer.data(), serializer.getBytesWritten());
  }

  displayHandler.getFrameCanvas().fillScreen(ILI9341_T4_COLOR_BLACK);
  displayHandler.getFrameCanvas().drawRect(0, 0, displayHandler.getFrameCanvas().width(), displayHandler.getFrameCanvas().height(), ILI9341_T4_COLOR_WHITE);
  if (batteryHandler.isReady()) { label.setText(String(batteryHandler.getStateOfCharge()) + " %"); }
  label.draw();
  
  displayHandler.updateTouch();
  displayHandler.updateScreen();

  halvoeHandheld::updateOrientationHandler();
}
