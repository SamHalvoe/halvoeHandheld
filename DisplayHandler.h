#pragma once

#include <array>

#include <Adafruit_GFX.h>
#include <ILI9341_T4.h>
#include <FT6236.h>

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
    static const uint8_t TFT_BACKLIGHT_PIN = 9;
    static const uint8_t TFT_RESET_PIN = 31;
    static const uint8_t TFT_DC_PIN = 0;
    static const uint8_t TFT_CS_PIN = 32;
    static const uint8_t TFT_MOSI_PIN = 26;
    static const uint8_t TFT_MISO_PIN = 1;
    static const uint8_t TFT_SCK_PIN = 27;

    static const uint8_t TOUCH_RESET_PIN = 3;
    static const uint8_t TOUCH_SCL_PIN = 24;
    static const uint8_t TOUCH_SDA_PIN = 25;
    static const uint8_t TOUCH_THRESHHOLD = 64;

  private:
    ILI9341_T4::ILI9341Driver m_displayDevice;
    ILI9341_T4::DiffBuffStatic<8192> m_diffBuffer1;
    ILI9341_T4::DiffBuffStatic<8192> m_diffBuffer2;
    GFXcanvas16 m_frameCanvas;
    std::array<uint16_t, 256> m_colorPalette;

    uint8_t touchUpdateInterval = 50;
    elapsedMillis timeSinceTouchUpdated;
    FT6236 m_touchDevice;
    std::array<TouchPoint, 2> m_touchPoints;

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
      m_frameCanvas(DisplayHandlerGlobal::TFT_PIXEL_HEIGHT, DisplayHandlerGlobal::TFT_PIXEL_WIDTH),
      m_touchDevice(Wire2)
    {
      setupColorPalette();
    }

    bool begin()
    {
      Serial.println("---- Display Setup Begin ----");
      
      analogWrite(TFT_BACKLIGHT_PIN, 255);

      delay(3000);

      m_displayDevice.output(&Serial);                // output debug infos to serial port.     
      
      bool isSuccessfulDisplay = m_displayDevice.begin(TFT_SPI_FREQ);

      if (not isSuccessfulDisplay)
      {
        Serial.println("ERROR: Could not initialise displayDevice!");
      }
      
      m_displayDevice.setRotation(1);                 // landscape mode 240x320
      m_displayDevice.setFramebuffer(DisplayHandlerGlobal::frameBuffer);  // set the internal framebuffer (enables double buffering)
      m_displayDevice.setDiffBuffers(&m_diffBuffer1, &m_diffBuffer2); // set the 2 diff buffers => activate differential updates.
      m_displayDevice.setDiffGap(6);                  // use a small gap for the diff buffers
      m_displayDevice.setRefreshRate(120);            // around 120hz for the display refresh rate. 
      m_displayDevice.setVSyncSpacing(2);             // set framerate = refreshrate/2 (and enable vsync at the same time).
      m_displayDevice.invertDisplay(true);

      m_displayDevice.clear(ILI9341_T4_COLOR_BLACK);
      delay(1000);

      //rectangle.fillScreen(0x01);
      m_frameCanvas.cp437(true);
      m_frameCanvas.setTextSize(1);
      m_frameCanvas.fillScreen(ILI9341_T4_COLOR_GREEN);
      m_displayDevice.update(m_frameCanvas.getBuffer());

      Serial.println("-- Touch Device Setup Begin --");

      pinMode(TOUCH_RESET_PIN, OUTPUT);
      digitalWrite(TOUCH_RESET_PIN, LOW);
      delay(500);
      digitalWrite(TOUCH_RESET_PIN, HIGH);
      delay(2000);

      bool isSuccessfulTouch = m_touchDevice.begin(TOUCH_THRESHHOLD);

      if (not isSuccessfulTouch)
      {
        Serial.println("ERROR: Could not initialise touchDevice!");
      }

      m_touchDevice.debug();

      Serial.println("-- Touch Device Setup End --");
      Serial.println("---- Display Setup End ----");

      return isSuccessfulDisplay && isSuccessfulTouch;
    }

    void updateScreen()
    {
      if (m_touchPoints[0].pm_x != FT6236_INVALID_STATE)
      {
        m_frameCanvas.drawCircle(m_touchPoints[0].pm_y, 240 - m_touchPoints[0].pm_x, 15, ILI9341_T4_COLOR_RED);
      }

      if (m_touchPoints[1].pm_x != FT6236_INVALID_STATE)
      {
        m_frameCanvas.drawCircle(m_touchPoints[1].pm_y, 240 - m_touchPoints[1].pm_x, 15, ILI9341_T4_COLOR_GREEN);
      }

      m_displayDevice.overlayFPS(m_frameCanvas.getBuffer());
      m_displayDevice.update(m_frameCanvas.getBuffer());
    }

    void updateTouch()
    {
      if (timeSinceTouchUpdated > touchUpdateInterval)
      {
        m_touchDevice.readData();

        /*if (m_touchDevice.touches == 2) ?!?!
        {
          uint16_t firstTouchID = m_touchDevice.touchID[0];
          uint16_t secondTouchID = m_touchDevice.touchID[1];
        }*/

        uint16_t firstTouchID = m_touchDevice.touchID[0];
        uint16_t secondTouchID = m_touchDevice.touchID[1];

        if (firstTouchID == FT6236_INVALID_STATE)
        {
          firstTouchID = 1;
        }
        else if (secondTouchID == FT6236_INVALID_STATE)
        {
          secondTouchID = 1;
        }

        m_touchPoints[firstTouchID].pm_x = m_touchDevice.touchX[0];
        m_touchPoints[firstTouchID].pm_y = m_touchDevice.touchY[0];

        m_touchPoints[secondTouchID].pm_x = m_touchDevice.touchX[1];
        m_touchPoints[secondTouchID].pm_y = m_touchDevice.touchY[1];

        if (m_touchDevice.touches > 0)
        {
          Serial.print(m_touchDevice.touches);
          Serial.print(" | ");
          Serial.print(m_touchDevice.touchID[0]);
          Serial.print(" ");
          Serial.print(m_touchDevice.touchID[1]);
          Serial.print(" ");
          Serial.print(m_touchDevice.touchX[0]);
          Serial.print(" ");
          Serial.print(m_touchDevice.touchX[1]);
          Serial.print(" ");
          Serial.print(m_touchDevice.touchY[0]);
          Serial.print(" ");
          Serial.print(m_touchDevice.touchY[1]);
          Serial.println();
          Serial.print("p1 ");
          Serial.print(m_touchPoints[0].pm_x);
          Serial.print(" ");
          Serial.print(m_touchPoints[0].pm_y);
          Serial.println();
          Serial.print("p2 ");
          Serial.print(m_touchPoints[1].pm_x);
          Serial.print(" ");
          Serial.print(m_touchPoints[1].pm_y);
          Serial.println();
        }

        timeSinceTouchUpdated = 0;
      }
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
