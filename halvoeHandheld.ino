#include "halvoeLogging.h"
#include "DisplayHandler.h"
#include "halvoeLabel.h"

DisplayHandler displayHandler;
Label label(&displayHandler.getFrameCanvas(), "Test", 64, 64);

void setup()
{
  halvoeHandheld::setupSerial();
  halvoeHandheld::logVersion();

  displayHandler.begin();
  label.draw();
  //displayHandler.setChangedArea(0, 0, DisplayHandler::TFT_PIXEL_WIDTH, DisplayHandler::TFT_PIXEL_HEIGHT);
  displayHandler.setChangedArea(label.getBoundingBox());
}

void loop()
{
  displayHandler.updateScreen();
  delay(250);
}
