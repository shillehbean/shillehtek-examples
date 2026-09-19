// Attach an interrupt to an IR sensor input to count pulses, compute RPM every second, and display the value on an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ir-sensor-measure-rpm-oled
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const int SENSOR = 2;
const float PULSES_PER_REV = 1.0;      // stripes/blades per rotation
volatile unsigned long pulses = 0;
unsigned long lastCalc = 0;

void countPulse() { pulses++; }

void setup() {
  pinMode(SENSOR, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR), countPulse, FALLING);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  lastCalc = millis();
}

void loop() {
  if (millis() - lastCalc >= 1000) {
    noInterrupts();
    unsigned long p = pulses; pulses = 0;
    interrupts();
    lastCalc = millis();

    float rpm = (p / PULSES_PER_REV) * 60.0;

    oled.clearDisplay();
    oled.setTextSize(1); oled.setCursor(0, 0);  oled.print("Tachometer");
    oled.setTextSize(3); oled.setCursor(0, 22); oled.print((int)rpm);
    oled.setTextSize(1); oled.setCursor(0, 52); oled.print("RPM");
    oled.display();
  }
}
