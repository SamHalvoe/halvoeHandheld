#pragma once

#include <array>

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_FT6206.h>

#include "halvoeBoundingBox.h"
#include "GFXcanvasExtmem.h"

//EXTMEM GFXcanvas8Extmem rectangle(32, 48);

class DisplayHandler
{
  public:
    static const uint32_t TFT_SPI_FREQ = 30000000;
    static const uint8_t TFT_BACKLIGHT_PIN = 25;
    static const uint8_t TFT_RESET_PIN = 9;
    static const uint8_t TFT_DC_PIN = 10;
    static const uint8_t TFT_CS_PIN = 8;
    static const uint8_t TFT_MOSI_PIN = 11;
    static const uint8_t TFT_MISO_PIN = 12;
    static const uint8_t TFT_SCK_PIN = 13;
    //static const uint8_t TOUCH_SCL_PIN = 16;
    //static const uint8_t TOUCH_SDA_PIN = 17;

    //static const uint8_t MAX_TOUCH_COUNT = 5;

  private:
    Adafruit_ILI9341 m_displayDevice;
    std::array<uint16_t, 256> m_colorPalette;

    //Adafruit_FT6206 m_touchDevice;

  private:
    void setupColorPalette()
    {
      m_colorPalette.fill(ILI9341_BLACK);
      m_colorPalette.at(1) = ILI9341_RED;
      m_colorPalette.at(2) = ILI9341_GREEN;
      m_colorPalette.at(3) = ILI9341_BLUE;
    }

  public:
    DisplayHandler() :
      m_displayDevice(TFT_CS_PIN, TFT_DC_PIN, TFT_MOSI_PIN, TFT_SCK_PIN, TFT_RESET_PIN, TFT_MISO_PIN)
    {
      setupColorPalette();
    }

    bool begin()
    {
      Serial.println("---- Display Setup Begin ----");
      
      analogWrite(TFT_BACKLIGHT_PIN, 255);

      delay(3000);
      
      m_displayDevice.begin();
      
      m_displayDevice.setRotation(1);                 // landscape mode 240x320

      uint8_t x = m_displayDevice.readcommand8(ILI9341_RDMODE);
      Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
      x = m_displayDevice.readcommand8(ILI9341_RDMADCTL);
      Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
      x = m_displayDevice.readcommand8(ILI9341_RDPIXFMT);
      Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
      x = m_displayDevice.readcommand8(ILI9341_RDIMGFMT);
      Serial.print("Image Format: 0x"); Serial.println(x, HEX);
      x = m_displayDevice.readcommand8(ILI9341_RDSELFDIAG);
      Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 

      //m_touchDevice.begin(FT53XX_DEFAULT_ADDR, &Wire1);

      //rectangle.fillScreen(0x01);
      m_displayDevice.fillScreen(ILI9341_BLACK);
      delay(1000);
      m_displayDevice.fillScreen(ILI9341_GREEN);
      delay(1000);
      m_displayDevice.fillScreen(ILI9341_WHITE);

      Serial.println("---- Display Setup End ----");

      return true;
    }

    void updateScreen()
    {
      //m_displayDevice.overlayFPS(m_frameCanvas.getBuffer());

      //m_displayDevice.update(m_frameCanvas.getBuffer());
      m_displayDevice.fillScreen(ILI9341_GREEN);
    }
};
