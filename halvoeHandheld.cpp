#include <Arduino.h>

#include "halvoeLogging.h"
#include "DisplayHandler.h"
#include "halvoeLabel.h"

Logger logger;
DisplayHandler displayHandler;
Label label(&displayHandler.getFrameCanvas(), "Test", 64, 64);

void setup()
{
  logger.setupSerial();

  bool isSDInitSuccessful = SD.begin(BUILTIN_SDCARD);

  if (isSDInitSuccessful)
  {
    logger.println("SD init is successful.", Logger::LT_SERIAL);
    logger.setupFile();
  }
  else
  {
    logger.println("SD init failed!", Logger::LT_SERIAL);
  }

  logger.printVersion();
  logger.flushFile();

  Wire.begin();
  //Wire1.begin();
  Wire2.begin();

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
