// Reads IR data from a MAX30102/MAX30105 sensor, detects beats, computes BPM and a rolling average, and prints IR/BPM/Avg to the Serial Monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-max30102-stream-heart-rate-serial
// Parts used: https://shillehtek.com/products/max30102-heart-rate-pulse-oximeter-sensor-module-black-presoldered
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <MAX30105.h>
#include <heartRate.h>

MAX30105 sensor;
const byte AVG = 4;
byte rates[AVG];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int  beatAvg;

void setup() {
  Serial.begin(115200);
  if (!sensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 not found");
    while (1);
  }
  sensor.setup();             // sensible defaults
  sensor.setPulseAmplitudeRed(0x0A);
  sensor.setPulseAmplitudeGreen(0);
  Serial.println("Place a finger over the sensor...");
}

void loop() {
  long ir = sensor.getIR();
  if (checkForBeat(ir)) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60.0 / (delta / 1000.0);
    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= AVG;
      beatAvg = 0;
      for (byte i = 0; i < AVG; i++) beatAvg += rates[i];
      beatAvg /= AVG;
    }
  }
  Serial.print("IR=");        Serial.print(ir);
  Serial.print(" BPM=");      Serial.print(beatsPerMinute);
  Serial.print(" Avg=");      Serial.println(beatAvg);
}
