#include "DisplayHandler.hpp"

void DisplayHandler::setupColorPalette()
{
  m_colorPalette.fill(ILI9341_T4_COLOR_BLACK);
  m_colorPalette.at(1) = ILI9341_T4_COLOR_RED;
  m_colorPalette.at(2) = ILI9341_T4_COLOR_GREEN;
  m_colorPalette.at(3) = ILI9341_T4_COLOR_BLUE;
}

DisplayHandler::DisplayHandler(uint16_t* io_frameBuffer) :
  m_displayDevice(TFT_CS_PIN, TFT_DC_PIN, TFT_SCK_PIN, TFT_MOSI_PIN, TFT_MISO_PIN, TFT_RESET_PIN),
  m_frameCanvas(TFT_PIXEL_HEIGHT, TFT_PIXEL_WIDTH),
  m_frameBuffer(io_frameBuffer),
  m_touchDevice(Wire2)
{
  setupColorPalette();
}

bool DisplayHandler::begin()
{
  #if HALVOE_LOG_SERIAL_ENABLED
  Serial.println("---- Display Setup Begin ----");
  #endif // HALVOE_LOG_SERIAL_ENABLED

  analogWrite(TFT_BACKLIGHT_PIN, 255);

  delay(3000);

  #if HALVOE_LOG_SERIAL_ENABLED
  m_displayDevice.output(&Serial); // output debug infos to serial port.     
  #endif // HALVOE_LOG_SERIAL_ENABLED

  bool isSuccessfulDisplay = m_displayDevice.begin(TFT_SPI_FREQ);

  if (not isSuccessfulDisplay)
  {
    #if HALVOE_LOG_SERIAL_ENABLED
    Serial.println("ERROR: Could not initialise displayDevice!");
    #endif // HALVOE_LOG_SERIAL_ENABLED
  }
      
  m_displayDevice.setRotation(1);                 // landscape mode 240x320
  m_displayDevice.setFramebuffer(m_frameBuffer);  // set the internal framebuffer (enables double buffering)
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

  #if HALVOE_LOG_SERIAL_ENABLED
  Serial.println("-- Touch Device Setup Begin --");
  #endif // HALVOE_LOG_SERIAL_ENABLED

  Wire2.begin();
  delay(500);

  pinMode(TOUCH_RESET_PIN, OUTPUT);
  digitalWrite(TOUCH_RESET_PIN, LOW);
  delay(500);
  digitalWrite(TOUCH_RESET_PIN, HIGH);
  delay(2000);

  bool isSuccessfulTouch = m_touchDevice.begin(TOUCH_THRESHHOLD);

  if (not isSuccessfulTouch)
  {
    #if HALVOE_LOG_SERIAL_ENABLED
    Serial.println("ERROR: Could not initialise touchDevice!");
    #endif // HALVOE_LOG_SERIAL_ENABLED
  }

  m_touchDevice.debug();

  #if HALVOE_LOG_SERIAL_ENABLED
  Serial.println("-- Touch Device Setup End --");
  Serial.println("---- Display Setup End ----");
  #endif // HALVOE_LOG_SERIAL_ENABLED

  return isSuccessfulDisplay && isSuccessfulTouch;
}

void DisplayHandler::updateScreen()
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

void DisplayHandler::updateTouch()
{
  if (timeSinceTouchUpdated > touchUpdateInterval)
  {
    m_touchDevice.readData();

    uint16_t firstTouchID = m_touchDevice.touchID[0];
    uint16_t secondTouchID = m_touchDevice.touchID[1];

    if (firstTouchID < 2)
    {
      m_touchPoints[firstTouchID].pm_x = m_touchDevice.touchX[0];
      m_touchPoints[firstTouchID].pm_y = m_touchDevice.touchY[0];
    }

    if (secondTouchID < 2)
    {
      m_touchPoints[secondTouchID].pm_x = m_touchDevice.touchX[1];
      m_touchPoints[secondTouchID].pm_y = m_touchDevice.touchY[1];
    }

    if (m_touchDevice.touches > 0)
    {
      #if HALVOE_LOG_SERIAL_ENABLED && HALVOE_LOG_LEVEL_SERIAL >= 9
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
      #endif // HALVOE_LOG_SERIAL_ENABLED
    }

    timeSinceTouchUpdated = 0;
  }
}

void DisplayHandler::printStatus()
{
  m_displayDevice.printStatus();
}

const GFXcanvas16& DisplayHandler::getFrameCanvas() const
{
  return m_frameCanvas;
}

GFXcanvas16& DisplayHandler::getFrameCanvas()
{
  return m_frameCanvas;
}