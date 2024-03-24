#pragma once

#include <array>

#include <Adafruit_GFX.h>
#include <HX8357_t3n.h>
#include <Adafruit_FT5336.h>

const uint8_t TFT_BACKLIGHT_PIN = 9;
const uint8_t TFT_RESET_PIN = 7;
const uint8_t TFT_DC_PIN = 38;
const uint8_t TFT_CS_PIN = 0;
const uint8_t TFT_MOSI_PIN = 26;
const uint8_t TFT_MISO_PIN = 1;
const uint8_t TFT_SCK_PIN = 27;
const uint32_t TFT_SPI_FREQ = 30000000;
const uint8_t TOUCH_SCL_PIN = 16;
const uint8_t TOUCH_SDA_PIN = 17;
const uint16_t displayWidth = 320;
const uint16_t displayHeight = 480;
const uint32_t displayPixelNumber = displayWidth * displayHeight;

const uint8_t touchDeviceMaxTouches = 5;

HX8357_t3n displayDevice(TFT_CS_PIN, TFT_DC_PIN, TFT_RESET_PIN, TFT_MOSI_PIN, TFT_SCK_PIN, TFT_MISO_PIN);
DMAMEM uint16_t displayFrameBuffer[displayPixelNumber];

std::array<uint16_t, 4> displayPalette = { HX8357_BLACK, HX8357_RED, HX8357_GREEN, HX8357_BLUE };

GFXcanvas16 rectangle(200, 300);

Adafruit_FT5336 touchDevice;

void setupDisplay()
{
  Serial.println("---- Display Setup Begin ----");

  analogWrite(TFT_BACKLIGHT_PIN, 255);

  delay(2000);
  displayDevice.begin(TFT_SPI_FREQ);
  displayDevice.setFrameBuffer(displayFrameBuffer);
  displayDevice.updateChangedAreasOnly(true);

  displayDevice.fillScreen(HX8357_BLACK);
  displayDevice.updateScreen();

  Serial.println("-- Display Infos Begin --");

  uint8_t infoValue = displayDevice.readcommand8(HX8357_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(infoValue, HEX);
  infoValue = displayDevice.readcommand8(HX8357_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(infoValue, HEX);
  infoValue = displayDevice.readcommand8(HX8357_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(infoValue, HEX);
  infoValue = displayDevice.readcommand8(HX8357_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(infoValue, HEX);
  infoValue = displayDevice.readcommand8(HX8357_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(infoValue, HEX);

  Serial.println("-- Display Infos End --");

  //touchDevice.begin(FT53XX_DEFAULT_ADDR, &Wire1);

  elapsedMillis timeFullUpdate;

  for (uint8_t index = 0; index < 4; ++index)
  {
    timeFullUpdate = 0;
    rectangle.fillScreen(displayPalette.at(index));
    displayDevice.writeRect(0, 0, rectangle.width(), rectangle.height(), rectangle.getBuffer());
    displayDevice.updateScreen();
    Serial.println("timeUpdateScreen: " + String(timeFullUpdate) + " ms");
  }

  Serial.println("---- Display Setup End ----");
}
