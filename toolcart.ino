#include <Arduino.h>
#include "Adafruit_GC9107.h"
#define NUM_SWITCHES 2  // Number of switches

//#define TFT_MOSI D10  // VSPI MOSI
//#define TFT_SCLK D8   // VSPI SCLK
#define LCD_CS   D2     // SPI chip select
#define LCD_DC   D5     // Data/command
#define LCD_RST  D4    // Reset pin
#define LCD_BL   D9     // Backlight

Adafruit_GC9107 display(128, 128, LCD_CS, LCD_DC, LCD_RST, LCD_BL);
const int switchPins[NUM_SWITCHES] = { 1, 17 };

void setup() {

  Serial.begin(115200);
  delay(100);
  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(LCD_BL, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  //pinMode(GFX_BL, OUTPUT);

  // Set all switch pins as INPUT_PULLUP
  for (int i = 0; i < NUM_SWITCHES; i++) {
    pinMode(switchPins[i], INPUT_PULLUP);
  }

  display.begin(10000000);
  display.setRotation(0);
  display.fillScreen(GC9107_BLACK);

    // Draw some test shapes
  display.drawPixel(10, 10, GC9107_WHITE);
  display.drawLine(20, 20, 60, 20, GC9107_RED);
  display.fillRect(30, 30, 30, 30, GC9107_GREEN);
  
  // Print text
  display.setTextColor(GC9107_YELLOW);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("Hello GC9107!");

}

void loop() {
  int LED_on = LOW;
  for (int i = 0; i < NUM_SWITCHES; i++) {
    int switchState = digitalRead(switchPins[i]);  // Reads HIGH (unpressed) or LOW (pressed)
    if (switchState == LOW) {
      LED_on = HIGH;
    }
  }
  digitalWrite(LED_BUILTIN, LED_on);
  //digitalWrite(LCD_BL, !LED_on);
  delay(100);
}

