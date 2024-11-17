#pragma once

#include <array>
#include <tgx.h>
#include <ILI9341_T4.h>

namespace halvoeHandheld
{
  const uint32_t TFT_SPI_FREQ = 30000000;
  const uint8_t TFT_BACKLIGHT_PIN = 9;
  const uint8_t TFT_RESET_PIN = 31;
  const uint8_t TFT_DC_PIN = 0;
  const uint8_t TFT_CS_PIN = 32;
  const uint8_t TFT_MOSI_PIN = 26;
  const uint8_t TFT_MISO_PIN = 1;
  const uint8_t TFT_SCK_PIN = 27;

  class DisplayHandler
  {
    private:
      ILI9341_T4::ILI9341Driver m_displayDevice;
      ILI9341_T4::DiffBuffStatic<8192>* m_diffBuffer1;
      ILI9341_T4::DiffBuffStatic<8192>* m_diffBuffer2;
      uint16_t* m_internalFrameBuffer = nullptr;
      uint16_t* m_frameBuffer = nullptr;
      tgx::Image<tgx::RGB565> m_frame;
      std::array<tgx::RGB565, 256> m_colorPalette;

    private:
      void setupColorPalette();

    public:
      DisplayHandler(uint16_t* io_internalFrameBuffer, uint16_t* io_frameBuffer,
        ILI9341_T4::DiffBuffStatic<8192>* io_diffBuffer1,
        ILI9341_T4::DiffBuffStatic<8192>* io_diffBuffer2);
      bool begin(Stream& out_loggingStreamLibraries);
      void update();
      void printStatus();
      const tgx::Image<tgx::RGB565>& getFrame() const;
      tgx::Image<tgx::RGB565>& getFrame();
   };
}

