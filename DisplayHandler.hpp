#pragma once

#include <array>

#include <Adafruit_GFX.h>
#include <ILI9341_T4.h>
#include <FT6236.h>

#include "halvoeLogging.hpp"
#include "halvoeBoundingBox.hpp"

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
    static const uint8_t TOUCH_THRESHHOLD = 32;

    static const uint16_t TFT_PIXEL_WIDTH = 240;
    static const uint16_t TFT_PIXEL_HEIGHT = 320;
    static const uint32_t TFT_PIXEL_COUNT = TFT_PIXEL_WIDTH * TFT_PIXEL_HEIGHT;

  private:
    ILI9341_T4::ILI9341Driver m_displayDevice;
    ILI9341_T4::DiffBuffStatic<8192> m_diffBuffer1;
    ILI9341_T4::DiffBuffStatic<8192> m_diffBuffer2;
    GFXcanvas16 m_frameCanvas;
    uint16_t* m_frameBuffer = nullptr;
    std::array<uint16_t, 256> m_colorPalette;

    uint8_t touchUpdateInterval = 50;
    elapsedMillis timeSinceTouchUpdated;
    FT6236 m_touchDevice;
    std::array<TouchPoint, 2> m_previousTouchPoints;
    std::array<TouchPoint, 2> m_touchPoints;

  private:
    void setupColorPalette();

  public:
    DisplayHandler(uint16_t* io_frameBuffer);
    bool begin();
    void updateScreen();
    void updateTouch();
    void printStatus();
    const GFXcanvas16& getFrameCanvas() const;
    GFXcanvas16& getFrameCanvas();
};
