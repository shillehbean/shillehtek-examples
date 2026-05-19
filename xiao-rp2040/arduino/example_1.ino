// Enables NeoPixel power via a GPIO and cycles the on-board WS2812 RGB LED through red, green, and blue using the Adafruit NeoPixel library.
//
// Buy this module: https://shillehtek.com/products/seeed-studio-xiao-rp2040-pre-soldered-with-usb-to-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/seeed-studio-xiao-rp2040-pre-soldered-with-usb-to-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO RP2040 - Cycle the on-board WS2812 RGB LED
// Library: Adafruit NeoPixel (Library Manager)
// Board: "Seeed XIAO RP2040" (Arduino-Pico core by Earle Philhower)

#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN  12     // D2 / GP12
#define NEOPIXEL_PWR  11     // GP11 enables NeoPixel power

Adafruit_NeoPixel pixel(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(NEOPIXEL_PWR, OUTPUT);
  digitalWrite(NEOPIXEL_PWR, HIGH);   // Enable LED power
  pixel.begin();
  pixel.setBrightness(40);
}

void loop() {
  pixel.setPixelColor(0, pixel.Color(255, 0, 0));   pixel.show(); delay(400);
  pixel.setPixelColor(0, pixel.Color(0, 255, 0));   pixel.show(); delay(400);
  pixel.setPixelColor(0, pixel.Color(0, 0, 255));   pixel.show(); delay(400);
}
