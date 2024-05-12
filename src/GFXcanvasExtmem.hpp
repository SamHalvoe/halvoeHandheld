#pragma once

#include <Adafruit_GFX.h>

/// A GFX 8-bit canvas context for graphics in PSRAM
class GFXcanvas8Extmem : public Adafruit_GFX
{
  public:
    GFXcanvas8Extmem(uint16_t w, uint16_t h);
    ~GFXcanvas8Extmem(void);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void fillScreen(uint16_t color);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    uint8_t getPixel(int16_t x, int16_t y) const;
    /**********************************************************************/
    /*!
    @brief    Get a pointer to the internal buffer memory
    @returns  A pointer to the allocated buffer
    */
    /**********************************************************************/
    uint8_t *getBuffer(void) const { return buffer; }

    static void* operator new(size_t in_instanceSize)
    {
      return extmem_malloc(in_instanceSize);
    }

    static void operator delete(void* del_instancePointer)
    {
      extmem_free(del_instancePointer);
    }

  protected:
    uint8_t getRawPixel(int16_t x, int16_t y) const;
    void drawFastRawVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastRawHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    uint8_t *buffer; ///< Raster data: no longer private, allow subclass access
};

///  A GFX 16-bit canvas context for graphics in PSRAM
class GFXcanvas16Extmem : public Adafruit_GFX
{
  public:
    GFXcanvas16Extmem(uint16_t w, uint16_t h);
    ~GFXcanvas16Extmem(void);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void fillScreen(uint16_t color);
    void byteSwap(void);
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    uint16_t getPixel(int16_t x, int16_t y) const;

    /**********************************************************************/
    /*!
      @brief    Get a pointer to the internal buffer memory
      @returns  A pointer to the allocated buffer
    */
    /**********************************************************************/
    uint16_t *getBuffer(void) const { return buffer; }

    static void* operator new(size_t in_instanceSize)
    {
      return extmem_malloc(in_instanceSize);
    }

    static void operator delete(void* del_instancePointer)
    {
      extmem_free(del_instancePointer);
    }

  protected:
    uint16_t getRawPixel(int16_t x, int16_t y) const;
    void drawFastRawVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    void drawFastRawHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    uint16_t *buffer; ///< Raster data: no longer private, allow subclass access
};
