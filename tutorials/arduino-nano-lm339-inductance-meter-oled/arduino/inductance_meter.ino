// Drives an LC tank, measures the oscillation half-period with pulseIn(), computes inductance from a known tank capacitor, and displays status/text on an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-lm339-inductance-meter-oled
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const int PULSE = 13, SENSE = 11;
const double C = 2.2e-6;                     // tank capacitor in farads: enter the measured value

double readInductance() {
  digitalWrite(PULSE, HIGH); delay(5);       // charge the tank
  digitalWrite(PULSE, LOW);  delayMicroseconds(100);
  double half = pulseIn(SENSE, HIGH, 5000);  // one HIGH pulse = half a period, in microseconds
  if (half == 0) return -1;                  // nothing rang: no coil, or out of range
  double f = 1.0 / (2.0 * half * 1e-6);      // resonant frequency in Hz
  return 1.0 / (4.0 * PI * PI * f * f * C);  // L = 1 / (4 pi^2 f^2 C), in henries
}

void setup() {
  pinMode(PULSE, OUTPUT); pinMode(SENSE, INPUT);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
}

void loop() {
  double sum = 0; int n = 0;
  for (int i = 0; i < 10; i++) {             // average ten kicks
    double L = readInductance();
    if (L > 0) { sum += L; n++; }
  }
  oled.clearDisplay();
  oled.setTextSize(2); oled.setCursor(0, 0); oled.print("Inductance");
  oled.setCursor(0, 30);
  if (n == 0) oled.print("no coil");
  else {
    double L = sum / n;
    if (L < 1e-3) { oled.print(L * 1e6, 1); oled.print(" uH"); }
    else          { oled.print(L * 1e3, 2); oled.print(" mH"); }
  }
  oled.display();
  delay(300);
}
