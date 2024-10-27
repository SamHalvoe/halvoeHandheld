#include <SerialInterface.hpp>
#include "halvoeLogging.hpp"
#include "BatteryHandler.hpp"
#include "TrackballHandler.hpp"
#include "HapticDriver.hpp"
#include "OrientationHandler.hpp"
#include "SerialAudioController.hpp"
#include "DisplayHandler.hpp"
#include "halvoeLabel.hpp"

DMAMEM uint16_t frameBuffer[DisplayHandler::TFT_PIXEL_COUNT];

DisplayHandler displayHandler(frameBuffer);
Label label(&displayHandler.getFrameCanvas(), "Test", 64, 64);
TrackballHandler trackballHandler0;
TrackballHandler trackballHandler1;
BatteryHandler batteryHandler(Wire1);
halvoe::SerialAudioController audioController(Serial3);
HapticDriver hapticDriver;
OrientationHandler orientationHandler;

void setup()
{
  #if HALVOE_LOG_SERIAL_ENABLED
  halvoeHandheld::setupSerial();
  Serial.print(halvoeHandheld::getVersionString());
  #endif // HALVOE_LOG_SERIAL_ENABLED

  audioController.setup();
  displayHandler.begin();

  Wire.begin();
  Wire1.begin();

  batteryHandler.begin();
  hapticDriver.setup();
  orientationHandler.setup();

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
    Serial.println("trackballHandler1 clicked");

    if (audioController.playFile("ddd4416.wav"))
    {
      Serial.println("playFile() is ok");
    }
  }
  else if (trackballHandler0.clicked())
  {
    Serial.println("trackballHandler0 clicked");

    if (audioController.endPlayback())
    {
      Serial.println("endPlayback() is ok");
    }
  }

  displayHandler.getFrameCanvas().fillScreen(ILI9341_T4_COLOR_BLACK);
  displayHandler.getFrameCanvas().drawRect(0, 0, displayHandler.getFrameCanvas().width(), displayHandler.getFrameCanvas().height(), ILI9341_T4_COLOR_WHITE);
  if (batteryHandler.isReady()) { label.setText(String(batteryHandler.getStateOfCharge()) + " %"); }
  label.draw();
  
  displayHandler.updateTouch();
  displayHandler.updateScreen();
  orientationHandler.update();
}
