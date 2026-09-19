// Reads an analog TDS sensor on A1, applies median filtering and temperature compensation, computes water PPM using the Gravity sensor curve, and displays the value on an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-tds-sensor-oled-ppm-meter
// Parts used: https://shillehtek.com/products/tds-water-sensor-module-arduino-raspberry-pi-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TdsSensorPin A1
#define VREF 5.0          // ADC reference voltage
#define SCOUNT 30         // samples for median filtering

Adafruit_SSD1306 display(128, 64, &Wire, -1);

int analogBuffer[SCOUNT];
int bufferIndex = 0;
float temperature = 25;   // compensation temperature
float tdsValue = 0;

void setup() {
  Serial.begin(115200);
  pinMode(TdsSensorPin, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  // sample every 40 ms into the ring buffer
  analogBuffer[bufferIndex] = analogRead(TdsSensorPin);
  bufferIndex = (bufferIndex + 1) % SCOUNT;
  delay(40);

  // median-filtered average voltage
  float averageVoltage = getMedianNum(analogBuffer, SCOUNT) * VREF / 1024.0;

  // temperature compensation, then the Gravity voltage to ppm curve
  float compensation = 1.0 + 0.02 * (temperature - 25.0);
  float v = averageVoltage / compensation;
  tdsValue = (133.42 * v * v * v - 255.86 * v * v + 857.39 * v) * 0.5;

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 20);
  display.print(tdsValue, 0);
  display.print(" ppm");
  display.display();
}
