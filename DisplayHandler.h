#pragma once

#include <array>

#include <Adafruit_GFX.h>
#include <ILI9341_T4.h>
#include <Adafruit_FT6206.h>

#include "halvoeBoundingBox.h"
#include "GFXcanvasExtmem.h"

//EXTMEM GFXcanvas8Extmem rectangle(32, 48);

namespace DisplayHandlerGlobal
{
  const uint16_t TFT_PIXEL_WIDTH = 240;
  const uint16_t TFT_PIXEL_HEIGHT = 320;
  const uint32_t TFT_PIXEL_COUNT = TFT_PIXEL_WIDTH * TFT_PIXEL_HEIGHT;

  DMAMEM uint16_t frameBuffer[TFT_PIXEL_COUNT];
}

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
    ILI9341_T4::ILI9341Driver m_displayDevice;
    ILI9341_T4::DiffBuffStatic<8192> m_diffBuffer1;
    ILI9341_T4::DiffBuffStatic<8192> m_diffBuffer2;
    GFXcanvas16 m_frameCanvas;
    std::array<uint16_t, 256> m_colorPalette;

    //Adafruit_FT6206 m_touchDevice;

  private:
    void setupColorPalette()
    {
      m_colorPalette.fill(ILI9341_T4_COLOR_BLACK);
      m_colorPalette.at(1) = ILI9341_T4_COLOR_RED;
      m_colorPalette.at(2) = ILI9341_T4_COLOR_GREEN;
      m_colorPalette.at(3) = ILI9341_T4_COLOR_BLUE;
    }

  public:
    DisplayHandler() :
      m_displayDevice(TFT_CS_PIN, TFT_DC_PIN, TFT_SCK_PIN, TFT_MOSI_PIN, TFT_MISO_PIN, TFT_RESET_PIN),
      m_frameCanvas(DisplayHandlerGlobal::TFT_PIXEL_HEIGHT, DisplayHandlerGlobal::TFT_PIXEL_WIDTH)
    {
      setupColorPalette();
    }

    bool begin()
    {
      Serial.println("---- Display Setup Begin ----");
      
      analogWrite(TFT_BACKLIGHT_PIN, 255);

      delay(3000);

      m_displayDevice.output(&Serial);                // output debug infos to serial port.     
      
      bool isSuccessful = m_displayDevice.begin(TFT_SPI_FREQ);

      if (not isSuccessful)
      {
        Serial.println("ERROR: Could not initialise displayDevice!");

        return false;
      }
      
      m_displayDevice.setRotation(1);                 // landscape mode 240x320
      m_displayDevice.setFramebuffer(DisplayHandlerGlobal::frameBuffer);  // set the internal framebuffer (enables double buffering)
      m_displayDevice.setDiffBuffers(&m_diffBuffer1, &m_diffBuffer2); // set the 2 diff buffers => activate differential updates.
      m_displayDevice.setDiffGap(6);                  // use a small gap for the diff buffers
      m_displayDevice.setRefreshRate(120);            // around 120hz for the display refresh rate. 
      m_displayDevice.setVSyncSpacing(2);             // set framerate = refreshrate/2 (and enable vsync at the same time). 

      m_displayDevice.clear(ILI9341_T4_COLOR_BLACK);
      delay(1000);

      //m_touchDevice.begin(FT53XX_DEFAULT_ADDR, &Wire1);

      //rectangle.fillScreen(0x01);
      m_frameCanvas.cp437(true);
      m_frameCanvas.setTextSize(1);
      m_frameCanvas.fillScreen(ILI9341_T4_COLOR_GREEN);
      m_displayDevice.update(m_frameCanvas.getBuffer());
      /*m_displayDevice.clear(ILI9341_T4_COLOR_BLACK);
      delay(1000);
      m_displayDevice.clear(ILI9341_T4_COLOR_GREEN);
      delay(1000);
      m_displayDevice.clear(ILI9341_T4_COLOR_WHITE);*/

      Serial.println("---- Display Setup End ----");

      return isSuccessful;
    }

    void updateScreen()
    {
      m_displayDevice.overlayFPS(m_frameCanvas.getBuffer());

      m_displayDevice.update(m_frameCanvas.getBuffer());
    }

    void printStatus()
    {
      m_displayDevice.printStatus();
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
