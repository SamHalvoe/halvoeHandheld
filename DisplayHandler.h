#pragma once

#include <array>

#include <Adafruit_GFX.h>
#include <HX8357_t3n.h>
#include <Adafruit_FT5336.h>

#include "halvoeBoundingBox.h"
#include "GFXcanvasExtmem.h"

EXTMEM GFXcanvas8Extmem rectangle(32, 48);

class DisplayHandler
{
  public:
    static const uint16_t TFT_PIXEL_WIDTH = 320;
    static const uint16_t TFT_PIXEL_HEIGHT = 480;
    static const uint32_t TFT_PIXEL_COUNT = TFT_PIXEL_WIDTH * TFT_PIXEL_HEIGHT;
    static const uint32_t TFT_SPI_FREQ = 30000000;
    static const uint8_t TFT_BACKLIGHT_PIN = 9;
    static const uint8_t TFT_RESET_PIN = 8;
    static const uint8_t TFT_DC_PIN = 0;
    static const uint8_t TFT_CS_PIN = 7;
    static const uint8_t TFT_MOSI_PIN = 26;
    static const uint8_t TFT_MISO_PIN = 1;
    static const uint8_t TFT_SCK_PIN = 27;
    //static const uint8_t TOUCH_SCL_PIN = 16;
    //static const uint8_t TOUCH_SDA_PIN = 17;

    //static const uint8_t MAX_TOUCH_COUNT = 5;

  private:
    HX8357_t3n m_displayDevice;
    GFXcanvas16 m_frameCanvas; //uint16_t m_frameBuffer[TFT_PIXEL_COUNT];
    std::array<uint16_t, 256> m_colorPalette;

    //Adafruit_FT5336 m_touchDevice;

  private:
    void setupColorPalette()
    {
      m_colorPalette.fill(HX8357_BLACK);
      m_colorPalette.at(1) = HX8357_RED;
      m_colorPalette.at(2) = HX8357_GREEN;
      m_colorPalette.at(3) = HX8357_BLUE;
    }

  public:
    DisplayHandler() :
      m_displayDevice(TFT_CS_PIN, TFT_DC_PIN, TFT_RESET_PIN, TFT_MOSI_PIN, TFT_SCK_PIN, TFT_MISO_PIN),
      m_frameCanvas(TFT_PIXEL_WIDTH, TFT_PIXEL_HEIGHT)
    {
      setupColorPalette();
    }

    bool begin()
    {
      Serial.println("---- Display Setup Begin ----");
      
      analogWrite(TFT_BACKLIGHT_PIN, 255);

      delay(1000);
      m_displayDevice.begin(TFT_SPI_FREQ);
      m_displayDevice.setFrameBuffer(/*m_frameBuffer);*/m_frameCanvas.getBuffer());
      m_displayDevice.useFrameBuffer(true);
      m_displayDevice.updateChangedAreasOnly(true);

      m_displayDevice.fillScreen(HX8357_BLACK);
      m_displayDevice.updateScreen();

      Serial.println("-- Display Infos Begin --");

      uint8_t displayPowerMode = m_displayDevice.readcommand8(HX8357_RDMODE);
      Serial.print("Display Power Mode: 0x"); Serial.println(displayPowerMode, HEX);
      uint8_t madCtlMode = m_displayDevice.readcommand8(HX8357_RDMADCTL);
      Serial.print("MADCTL Mode: 0x"); Serial.println(madCtlMode, HEX);
      uint8_t pixelFormat = m_displayDevice.readcommand8(HX8357_RDPIXFMT);
      Serial.print("Pixel Format: 0x"); Serial.println(pixelFormat, HEX);
      uint8_t imageFormat = m_displayDevice.readcommand8(HX8357_RDIMGFMT);
      Serial.print("Image Format: 0x"); Serial.println(imageFormat, HEX);
      uint8_t selfDiagnostic = m_displayDevice.readcommand8(HX8357_RDSELFDIAG);
      Serial.print("Self Diagnostic: 0x"); Serial.println(selfDiagnostic, HEX);

      Serial.println("-- Display Infos End --");

      //m_touchDevice.begin(FT53XX_DEFAULT_ADDR, &Wire1);

      rectangle.fillScreen(0x01);
      m_displayDevice.writeRect8BPP(0, 0, rectangle.width(), rectangle.height(), rectangle.getBuffer(), m_colorPalette.data());
      updateScreen();

      Serial.println("---- Display Setup End ----");

      return selfDiagnostic > 0x00 && selfDiagnostic < 0xFF;
    }

    void updateScreen()
    {
      elapsedMillis timeUpdateScreen;
      m_displayDevice.updateScreen();
      Serial.println("timeUpdateScreen: " + String(timeUpdateScreen) + " ms");

      m_displayDevice.updateChangedAreasOnly(true);
    }

    void updateFullScreenOnce()
    {
      m_displayDevice.updateChangedAreasOnly(false);
    }

    void clearChangedArea()
    {
      m_displayDevice.clearChangedRange();
    }

    void setChangedArea(int16_t in_x, int16_t in_y, int16_t in_width, int16_t in_height)
    {
      m_displayDevice.updateChangedRange(in_x, in_y, in_width, in_height);
    }

    void setChangedArea(const BoundingBox& in_boundingBox)
    {
      m_displayDevice.updateChangedRange(in_boundingBox.getX(), in_boundingBox.getY(),
                                         in_boundingBox.getWidth() + 1, in_boundingBox.getHeigth() + 1);
    }

    const GFXcanvas16& getFrameCanvas() const
    {
      return m_frameCanvas;
    }

    GFXcanvas16& getFrameCanvas()
    {
      return m_frameCanvas;
    }
};
