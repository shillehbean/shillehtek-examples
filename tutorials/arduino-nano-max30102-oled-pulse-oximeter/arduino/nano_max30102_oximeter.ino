// Arduino sketch that reads the MAX30102/ MAX30105 IR data to detect heart beats, computes BPM with a running average, and displays the result on an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-max30102-oled-pulse-oximeter
// Parts used: https://shillehtek.com/products/max30102-heart-rate-pulse-oximeter-sensor-module-black-presoldered
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <MAX30105.h>
#include <heartRate.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

MAX30105 sensor;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const byte AVG = 4;
byte rates[AVG]; byte rateSpot = 0;
long lastBeat = 0; float bpm; int beatAvg;

void setup() {
  Serial.begin(115200);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if (!sensor.begin(Wire, I2C_SPEED_FAST)) {
    oled.setTextSize(1); oled.setCursor(0, 0); oled.print("MAX30102 not found");
    oled.display(); while (1);
  }
  sensor.setup();
  sensor.setPulseAmplitudeRed(0x0A);
  sensor.setPulseAmplitudeGreen(0);
}

void loop() {
  long ir = sensor.getIR();
  if (checkForBeat(ir)) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    bpm = 60.0 / (delta / 1000.0);
    if (bpm < 255 && bpm > 20) {
      rates[rateSpot++] = (byte)bpm; rateSpot %= AVG;
      beatAvg = 0;
      for (byte i = 0; i < AVG; i++) beatAvg += rates[i];
      beatAvg /= AVG;
    }
  }
  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setTextSize(2); oled.setCursor(0, 4);
  oled.print("HR: "); oled.print(beatAvg);
  oled.setTextSize(1); oled.setCursor(0, 40);
  oled.print(ir < 50000 ? "No finger" : "Hold finger still");
  oled.display();
}
