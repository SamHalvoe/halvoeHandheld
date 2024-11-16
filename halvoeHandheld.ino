#include <SerialInterface.hpp>
#include "halvoeVersion.hpp"
#include "halvoeLog.hpp"
#include "halvoeSDHandler.hpp"
#include "BatteryHandler.hpp"
#include "TrackballHandler.hpp"
#include "HapticDriver.hpp"
#include "OrientationHandler.hpp"
#include "SerialAudioController.hpp"
#include "DisplayHandler.hpp"
#include "halvoeLabel.hpp"

using namespace halvoeHandheld;

SDHandler sdHandler;
LogFileManager logFileManager;

DMAMEM ILI9341_T4::DiffBuffStatic<8192> diffBuffer1;
DMAMEM ILI9341_T4::DiffBuffStatic<8192> diffBuffer2;
DMAMEM uint16_t internalFrameBuffer[DisplayHandler::TFT_PIXEL_COUNT];
DMAMEM uint16_t frameBuffer[DisplayHandler::TFT_PIXEL_COUNT];
DisplayHandler displayHandler(internalFrameBuffer, frameBuffer, &diffBuffer1, &diffBuffer2);
Label label(displayHandler.getFrame(), "Test", 64, 64);

TrackballHandler trackballHandler0;
TrackballHandler trackballHandler1;
BatteryHandler batteryHandler(Wire1);
HapticDriver hapticDriver;
OrientationHandler orientationHandler;
SerialAudioController audioController(Serial3);

void setup()
{
  Serial.begin(115200);
  delay(2000);
  LOG_INFO("Enter setup...");

  sdHandler.setup();
  logFileManager.setup();
  LOG_INFO(getVersionString());
  logFileManager.handleCrashReport();

  audioController.setup();
  displayHandler.begin(logFileManager.getLogStreamLibraries());

  Wire.begin();
  Wire.setClock(1000000);
  Wire1.begin();
  Wire1.setClock(1000000);

  batteryHandler.begin();
  hapticDriver.setup();
  orientationHandler.setup();

  trackballHandler0.begin(Wire);
  trackballHandler1.begin(Wire1);

  LOG_INFO("Leave setup...");
}

void loop()
{
  trackballHandler0.update();
  trackballHandler1.update();
  batteryHandler.update();

  if (trackballHandler1.clicked())
  {
    LOG_INFO("trackballHandler1 clicked");

    if (audioController.playFile("ddd4416.wav"))
    {
      LOG_INFO("playFile() is ok");
    }
  }
  else if (trackballHandler0.clicked())
  {
    LOG_INFO("trackballHandler0 clicked");

    if (audioController.endPlayback())
    {
      LOG_INFO("endPlayback() is ok");
    }
  }

  displayHandler.getFrame().fillScreen(tgx::RGB565_Black);
  displayHandler.getFrame().drawRect({0, displayHandler.getFrame().width() - 1, 0, displayHandler.getFrame().height() - 1}, tgx::RGB565_White);
  //if (batteryHandler.isReady()) { label.setText(String(batteryHandler.getStateOfCharge()) + " %"); }
  if (label.getBoundingBox().contains(displayHandler.getTouchPoint0())) { label.setOutlineColor(tgx::RGB565_Red); } else { label.setOutlineColor(tgx::RGB565_White); }
  label.draw();
  
  displayHandler.updateTouch();
  displayHandler.updateScreen();
  orientationHandler.update();

  logFileManager.flush();
  logFileManager.flushLibraries();
}
