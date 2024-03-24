#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>
#include <Adafruit_FT5336.h>

const uint8_t TFT_BACKLIGHT_PIN = 9;
const uint8_t TFT_RESET_PIN = 7;
const uint8_t TFT_DC_PIN = 8;
const uint8_t TFT_CS_PIN = 0;
const uint8_t TFT_MOSI_PIN = 26;
const uint8_t TFT_MISO_PIN = 1;
const uint8_t TFT_SCK_PIN = 27;
const uint32_t TFT_SPI_FREQ = 24000000;
const uint8_t TOUCH_SCL_PIN = 16;
const uint8_t TOUCH_SDA_PIN = 17;
const uint16_t displayWidth = 480;
const uint16_t displayHeight = 320;

const uint8_t touchDeviceMaxTouches = 5;

Adafruit_HX8357 displayDevice(&SPI1, TFT_CS_PIN, TFT_DC_PIN, TFT_RESET_PIN, HX8357D);
//Adafruit_HX8357 displayDevice(TFT_CS_PIN, TFT_DC_PIN, TFT_MOSI_PIN, TFT_SCK_PIN, TFT_RESET_PIN, TFT_MISO_PIN, HX8357D);
Adafruit_FT5336 touchDevice;

void setupDisplay()
{
  Serial.println("---- Display Setup Begin ----");

  analogWrite(TFT_BACKLIGHT_PIN, 255);

  delay(5000);
  displayDevice.begin(TFT_SPI_FREQ);
  //touchDevice.begin(FT53XX_DEFAULT_ADDR, &Wire1);

  Serial.println("-- Display Infos Begin --");

  uint8_t x = displayDevice.readcommand8(HX8357_RDPOWMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = displayDevice.readcommand8(HX8357_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = displayDevice.readcommand8(HX8357_RDCOLMOD);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = displayDevice.readcommand8(HX8357_RDDIM);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = displayDevice.readcommand8(HX8357_RDDSDR);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 

  Serial.println("-- Display Infos End --");

  displayDevice.fillScreen(HX8357_GREEN);
  //displayDevice.fillRect(0, 0, 64, 64, HX8357_GREEN);

  Serial.println("---- Display Setup End ----");
}
