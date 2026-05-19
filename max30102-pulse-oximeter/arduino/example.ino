// Arduino example using the SparkFun MAX3010x library to read IR values from the MAX30102 and calculate/print beats-per-minute (BPM) with a rolling average.
//
// Buy this module: https://shillehtek.com/products/max30102-heart-rate-pulse-oximeter-sensor-module-black-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max30102-heart-rate-pulse-oximeter-sensor-module-black-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// MAX30102 Heart Rate Sensor - Arduino Example
// Uses the SparkFun MAX3010x library
// Install: Arduino Library Manager -> search "SparkFun MAX3010x"
// I2C Pins: A4 (SDA), A5 (SCL)

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

void setup() {
  Serial.begin(9600);
  Serial.println("MAX30102 Heart Rate Sensor");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 not found. Check wiring.");
    while (1);
  }

  Serial.println("Place your finger on the sensor.");
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
}

void loop() {
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;

      // Calculate average BPM
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.println(beatAvg);

  if (irValue < 50000)
    Serial.println("No finger detected");
}
