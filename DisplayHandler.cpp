#include "DisplayHandler.hpp"
#include "DisplayDefinitions.hpp"
#include "halvoeLog.hpp"

namespace halvoeHandheld
{
  void DisplayHandler::setupColorPalette()
  {
    m_colorPalette.fill(tgx::RGB565_Black);
    m_colorPalette.at(1) = tgx::RGB565_Red;
    m_colorPalette.at(2) = tgx::RGB565_Green;
    m_colorPalette.at(3) = tgx::RGB565_Blue;
  }

  DisplayHandler::DisplayHandler(uint16_t* io_internalFrameBuffer, uint16_t* io_frameBuffer,
                                 ILI9341_T4::DiffBuffStatic<8192>* io_diffBuffer1,
                                 ILI9341_T4::DiffBuffStatic<8192>* io_diffBuffer2) :
    m_displayDevice(TFT_CS_PIN, TFT_DC_PIN, TFT_SCK_PIN, TFT_MOSI_PIN, TFT_MISO_PIN, TFT_RESET_PIN),
    m_diffBuffer1(io_diffBuffer1), m_diffBuffer2(io_diffBuffer2),
    m_internalFrameBuffer(io_internalFrameBuffer), m_frameBuffer(io_frameBuffer),
    m_frame(io_frameBuffer, TFT_PIXEL_HEIGHT, TFT_PIXEL_WIDTH)
  {
    setupColorPalette();
  }

  bool DisplayHandler::begin(Stream& out_loggingStreamLibraries)
  {
    LOG_INFO("---- Display Setup Begin ----");

    analogWrite(TFT_BACKLIGHT_PIN, 255);
    m_displayDevice.output(&out_loggingStreamLibraries); // output debug infos to library logging stream.

    if (not m_displayDevice.begin(TFT_SPI_FREQ))
    {
      LOG_ERROR("Could not initialise displayDevice!");
      return false;
    }
      
    m_displayDevice.setRotation(1);                         // landscape mode 240x320
    m_displayDevice.setFramebuffer(m_internalFrameBuffer);  // set the internal framebuffer (enables double buffering)
    m_displayDevice.setDiffBuffers(m_diffBuffer1, m_diffBuffer2); // set the 2 diff buffers => activate differential updates.
    m_displayDevice.setDiffGap(6);                          // use a small gap for the diff buffers
    m_displayDevice.setRefreshRate(120);                    // around 120hz for the display refresh rate. 
    m_displayDevice.setVSyncSpacing(2);                     // set framerate = refreshrate/2 (and enable vsync at the same time).
    m_displayDevice.invertDisplay(true);
    m_displayDevice.clear(ILI9341_T4_COLOR_BLACK);
    delay(1000);

    m_frame.fillScreen(tgx::RGB565_Green);
    m_displayDevice.update(m_frameBuffer);

    LOG_INFO("---- Display Setup End ----");
    return true;
  }

  void DisplayHandler::update()
  {
    /*if (m_touchPoints.first.x > 0)
    {
      m_frame.drawCircleAA(m_touchPoints.first, 15, tgx::RGB565_Red);
      m_frame.drawFastHLine({ m_touchPoints.first.x - 2, m_touchPoints.first.y }, 5, tgx::RGB565_Red);
      m_frame.drawFastVLine({ m_touchPoints.first.x, m_touchPoints.first.y - 2 }, 5, tgx::RGB565_Red);
    }

    if (m_touchPoints.second.x > 0)
    {
      m_frame.drawCircleAA(m_touchPoints.second, 15, tgx::RGB565_Green);
      m_frame.drawFastHLine({ m_touchPoints.second.x - 2, m_touchPoints.second.y }, 5, tgx::RGB565_Green);
      m_frame.drawFastVLine({ m_touchPoints.second.x, m_touchPoints.second.y - 2 }, 5, tgx::RGB565_Green);
    }*/

    m_displayDevice.overlayFPS(m_frameBuffer);
    m_displayDevice.update(m_frameBuffer);
  }

  void DisplayHandler::printStatus()
  {
    m_displayDevice.printStatus();
  }

  const tgx::Image<tgx::RGB565>& DisplayHandler::getFrame() const
  {
    return m_frame;
  }

  tgx::Image<tgx::RGB565>& DisplayHandler::getFrame()
  {
    return m_frame;
  }
}
