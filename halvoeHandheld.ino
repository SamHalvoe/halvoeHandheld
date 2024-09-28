#include "halvoeLogging.h"
#include "DisplayHandler.h"
#include "halvoeLabel.h"
#include "TrackballHandler.hpp"

DisplayHandler displayHandler;
Label label(&displayHandler.getFrameCanvas(), "Test", 64, 64);
TrackballHandler trackballHandler0;
TrackballHandler trackballHandler1;

void setup()
{
  #if HALVOE_LOG_SERIAL_ENABLED
  halvoeHandheld::setupSerial();
  Serial.print(halvoeHandheld::getVersionString());
  #endif // HALVOE_LOG_SERIAL_ENABLED

  displayHandler.begin();

  Wire.begin();
  Wire1.begin();

  trackballHandler0.begin(Wire);
  trackballHandler1.begin(Wire1);
}

void loop()
{
  trackballHandler0.update();
  trackballHandler1.update();

  displayHandler.getFrameCanvas().fillScreen(ILI9341_T4_COLOR_BLACK);
  displayHandler.getFrameCanvas().drawRect(0, 0, displayHandler.getFrameCanvas().width(), displayHandler.getFrameCanvas().height(), ILI9341_T4_COLOR_WHITE);
  label.draw();
  
  displayHandler.updateTouch();
  displayHandler.updateScreen();
}
