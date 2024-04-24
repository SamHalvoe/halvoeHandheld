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
}

void loop()
{
  displayHandler.getFrameCanvas().fillScreen(ILI9341_T4_COLOR_BLACK);
  displayHandler.getFrameCanvas().drawRect(0, 0, displayHandler.getFrameCanvas().width(), displayHandler.getFrameCanvas().height(), ILI9341_T4_COLOR_WHITE);
  label.draw();

  displayHandler.updateTouch();
  displayHandler.updateScreen();
}
