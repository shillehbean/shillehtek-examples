// Arduino sketch that reads the MAX30105/MAX30102 sensor, detects beats to calculate BPM (and averaged BPM), and displays readings on an SSD1306 OLED (also prints to Serial).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-max30102-oled-heart-rate-spo2
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/max30102-heart-rate-pulse-oximeter-sensor-module-black-presoldered
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <MAX30105.h>
#include <heartRate.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

MAX30105 particleSensor;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const int RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute = 0;
int beatAvg = 0;

void setup() {
  Serial.begin(115200);
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 not found");
    while (1);
  }
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue)) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);
    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;
      int sum = 0;
      for (byte i = 0; i < RATE_SIZE; i++) sum += rates[i];
      beatAvg = sum / RATE_SIZE;
    }
  }
  oled.clearDisplay();
  oled.setCursor(0, 0); oled.setTextSize(1); oled.setTextColor(WHITE);
  oled.print("IR: "); oled.println(irValue);
  oled.setTextSize(2);
  oled.print("BPM "); oled.println(beatAvg);
  oled.display();
}
