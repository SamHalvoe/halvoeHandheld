#include <Arduino.h>

#include "halvoeLogging.hpp"
#include "DisplayHandler.hpp"
#include "halvoeLabel.hpp"

using namespace halvoeHandheld;

DisplayHandler displayHandler;
Label label(&displayHandler.getFrameCanvas(), "Test", 64, 64);

const uint8_t delaySetupSeconds = 15; // s

void delaySetup()
{
  Serial.print("Delay setup by ");
  Serial.print(delaySetupSeconds);
  Serial.print(" seconds: ");

  for (uint8_t seconds = 0; seconds < delaySetupSeconds; ++seconds)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println(" Continue setup!");
}

void setup()
{
  logger.setupSerial();

  if (CrashReport)
  {
    Serial.println(CrashReport);
    delay(30000);
  }

  delaySetup();

  Serial.println("DEBUG_00");
  CrashReport.breadcrumb(1, millis());
  bool isSDInitSuccessful = sd.begin(SdioConfig(FIFO_SDIO));
  CrashReport.breadcrumb(2, millis());
  Serial.println("DEBUG_01");

  if (isSDInitSuccessful)
  {
    logger.println("SD init is successful.", Logger::LT_SERIAL);
    CrashReport.breadcrumb(3, millis());
    logger.setupFile();
    CrashReport.breadcrumb(4, millis());
  }
  else
  {
    logger.println("SD init failed!", Logger::LT_SERIAL);
  }

  logger.printVersion();

  Serial.println("DEBUG_02");

  Wire.begin();
  //Wire1.begin();
  Wire2.begin();

  Serial.println("DEBUG_03");

  displayHandler.begin();

  CrashReport.breadcrumb(5, millis());
  if (not logger.flushFile())
  {
    Serial.println("Error: flushFile failed!");
  }
  CrashReport.breadcrumb(6, millis());
}

void loop()
{
  displayHandler.getFrameCanvas().fillScreen(ILI9341_T4_COLOR_BLACK);
  displayHandler.getFrameCanvas().drawRect(0, 0, displayHandler.getFrameCanvas().width(), displayHandler.getFrameCanvas().height(), ILI9341_T4_COLOR_WHITE);
  label.draw();
  
  displayHandler.updateTouch();
  displayHandler.updateScreen();

  /*if (timeSincePrintBatteryStats >= printBatteryStatsInterval)
  {
    printBatteryStats();
    timeSincePrintBatteryStats = 0;
  }*/
}
