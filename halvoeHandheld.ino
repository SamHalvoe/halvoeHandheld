#include <SerialInterface.hpp>
#include "halvoeVersion.hpp"
#include "halvoeLog.hpp"
#include "halvoeSDHandler.hpp"
#include "BatteryHandler.hpp"
#include "TrackballHandler.hpp"
#include "HapticDriver.hpp"
#include "OrientationHandler.hpp"
#include "SerialAudioController.hpp"
#include "DisplayDefinitions.hpp"
#include "DisplayHandler.hpp"
#include "TouchHandler.hpp"
#include "halvoeLabel.hpp"

using namespace halvoeHandheld;

SDHandler sdHandler;
LogFileManager logFileManager;

DMAMEM ILI9341_T4::DiffBuffStatic<8192> diffBuffer1;
DMAMEM ILI9341_T4::DiffBuffStatic<8192> diffBuffer2;
DMAMEM uint16_t internalFrameBuffer[TFT_PIXEL_COUNT];
DMAMEM uint16_t frameBuffer[TFT_PIXEL_COUNT];
DisplayHandler displayHandler(internalFrameBuffer, frameBuffer, &diffBuffer1, &diffBuffer2);
TouchHandler touchHandler;
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
  touchHandler.begin(logFileManager.getLogStreamLibraries());
  touchHandler.addEventCallback(Event::Type::pressed, [](const Event& in_event){ label.handleEventPressed(in_event); });
  touchHandler.addEventCallback(Event::Type::released, [](const Event& in_event) { label.handleEventReleased(in_event); });

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

  touchHandler.update();
  orientationHandler.update();
  //if (batteryHandler.isReady()) { label.setText(String(batteryHandler.getStateOfCharge()) + " %"); }
  label.draw();

  if (touchHandler.getFirstTouchPoint().x > 0)
  {
    displayHandler.getFrame().drawCircleAA(touchHandler.getFirstTouchPoint(), 15, tgx::RGB565_Red);
    displayHandler.getFrame().drawFastHLine({ touchHandler.getFirstTouchPoint().x - 2, touchHandler.getFirstTouchPoint().y }, 5, tgx::RGB565_Red);
    displayHandler.getFrame().drawFastVLine({ touchHandler.getFirstTouchPoint().x, touchHandler.getFirstTouchPoint().y - 2 }, 5, tgx::RGB565_Red);
  }

  if (touchHandler.getSecondTouchPoint().x > 0)
  {
    displayHandler.getFrame().drawCircleAA(touchHandler.getSecondTouchPoint(), 15, tgx::RGB565_Green);
    displayHandler.getFrame().drawFastHLine({ touchHandler.getSecondTouchPoint().x - 2, touchHandler.getSecondTouchPoint().y }, 5, tgx::RGB565_Green);
    displayHandler.getFrame().drawFastVLine({ touchHandler.getSecondTouchPoint().x, touchHandler.getSecondTouchPoint().y - 2 }, 5, tgx::RGB565_Green);
  }

  displayHandler.update();

  logFileManager.flush();
  logFileManager.flushLibraries();
}
