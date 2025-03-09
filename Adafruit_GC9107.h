#ifndef ADAFRUIT_GC9107_H
#define ADAFRUIT_GC9107_H

#include <Adafruit_GFX.h>
#include <SPI.h>

// Some color definitions (typical 16-bit color)
#define GC9107_BLACK   0x0000
#define GC9107_BLUE    0x001F
#define GC9107_RED     0xF800
#define GC9107_GREEN   0x07E0
#define GC9107_CYAN    0x07FF
#define GC9107_MAGENTA 0xF81F
#define GC9107_YELLOW  0xFFE0
#define GC9107_WHITE   0xFFFF

class Adafruit_GC9107 : public Adafruit_GFX {
public:
  // Constructor: width and height can be 128, 128 for your display
  Adafruit_GC9107(int16_t w, int16_t h, int8_t cs, int8_t dc, int8_t rst = -1, int8_t bl = -1);

  // Initialize the display (run init sequence)
  void begin(uint32_t freq = 10000000); // default 10 MHz SPI
  void setRotation(uint8_t r) override;
  void invertDisplay(bool i);

  // Basic drawing functions from Adafruit GFX
  void drawPixel(int16_t x, int16_t y, uint16_t color) override;

  // Optional: add fillRect, drawFastVLine, etc. if you want faster functions
  // ...

private:
  int8_t  _cs, _dc, _rst, _bl;
  uint32_t _freq;
  
  // Low-level SPI write functions
  void writeCommand(uint8_t cmd);
  void writeData(uint8_t data);
  void writeDataBytes(const uint8_t *data, uint32_t len);

  // The device-specific init sequence
  void initDisplay();
};

#endif
