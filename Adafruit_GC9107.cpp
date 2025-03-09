#include "Adafruit_GC9107.h"

static SPIClass spi = SPIClass(FSPI); // or HSPI, depending on your pins

// Constructor
Adafruit_GC9107::Adafruit_GC9107(int16_t w, int16_t h, int8_t cs, int8_t dc, int8_t rst, int8_t bl)
  : Adafruit_GFX(w, h), _cs(cs), _dc(dc), _rst(rst), _bl(bl)
{
  // Nothing else needed here; 'begin()' will set up pins
}

// Initialize the display
void Adafruit_GC9107::begin(uint32_t freq) {
  _freq = freq;

  // Configure pin modes
  pinMode(_cs, OUTPUT);
  pinMode(_dc, OUTPUT);
  if(_rst >= 0) { pinMode(_rst, OUTPUT); }
  if(_bl >= 0)  { pinMode(_bl, OUTPUT); digitalWrite(_bl, HIGH); }

  // SPI init
  spi.begin(); // default pins for VSPI
  // optional: spi.setFrequency(_freq);

  // Hardware reset
  if(_rst >= 0) {
    digitalWrite(_rst, HIGH);
    delay(10);
    digitalWrite(_rst, LOW);
    delay(10);
    digitalWrite(_rst, HIGH);
    delay(100);
  }

  // Now send the GC9107 init sequence
  initDisplay();
}

// The actual commands and data needed to initialize GC9107
void Adafruit_GC9107::initDisplay() {
  // Below are placeholder commands. You need the real GC9107 init sequence
  // from the datasheet or from Waveshare's example code.

  writeCommand(0xFE); // Example command
  writeData(0x01);

  writeCommand(0xEF);
  writeData(0x02);

  // ... Insert more init registers ...
  // ...
  
  // Finally, exit sleep mode, turn on display
  writeCommand(0x11); // Sleep Out
  delay(100);
  writeCommand(0x29); // Display ON
  delay(100);
}

// Set rotation
void Adafruit_GC9107::setRotation(uint8_t r) {
  // For a 128x128 display, handle MADCTL changes for rotation
  // Example code:
  writeCommand(0x36); // MADCTL
  switch(r & 3) {
    case 0:
      writeData(0x00); // Some combination for 0 degrees
      _width  = 128;
      _height = 128;
      break;
    case 1:
      writeData(0x60); // For 90 degrees
      _width  = 128;
      _height = 128;
      break;
    case 2:
      writeData(0xC0); // 180 degrees
      _width  = 128;
      _height = 128;
      break;
    case 3:
      writeData(0xA0); // 270 degrees
      _width  = 128;
      _height = 128;
      break;
  }
}

// Invert colors
void Adafruit_GC9107::invertDisplay(bool i) {
  writeCommand(i ? 0x21 : 0x20);
}

// Draw a single pixel
void Adafruit_GC9107::drawPixel(int16_t x, int16_t y, uint16_t color) {
  if((x < 0) ||(x >= width()) || (y < 0) || (y >= height())) return;

  // Set address window (column, row)
  writeCommand(0x2A);
  writeData(x >> 8);
  writeData(x & 0xFF);
  writeData(x >> 8);
  writeData(x & 0xFF);

  writeCommand(0x2B);
  writeData(y >> 8);
  writeData(y & 0xFF);
  writeData(y >> 8);
  writeData(y & 0xFF);

  // Write RAM
  writeCommand(0x2C);
  writeData(color >> 8);
  writeData(color & 0xFF);
}

// Low-level helper commands
void Adafruit_GC9107::writeCommand(uint8_t cmd) {
  digitalWrite(_dc, LOW);
  digitalWrite(_cs, LOW);
  spi.transfer(cmd);
  digitalWrite(_cs, HIGH);
}

void Adafruit_GC9107::writeData(uint8_t data) {
  digitalWrite(_dc, HIGH);
  digitalWrite(_cs, LOW);
  spi.transfer(data);
  digitalWrite(_cs, HIGH);
}

void Adafruit_GC9107::writeDataBytes(const uint8_t *data, uint32_t len) {
  digitalWrite(_dc, HIGH);
  digitalWrite(_cs, LOW);
  while(len--) {
    spi.transfer(*data++);
  }
  digitalWrite(_cs, HIGH);
}
