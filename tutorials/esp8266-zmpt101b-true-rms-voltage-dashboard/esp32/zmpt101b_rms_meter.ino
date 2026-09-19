// Samples the ZMPT101B AC sensor on A0, computes true RMS using a running-statistics filter, applies calibration (intercept and slope), and prints the measured voltage to Serial every second.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp8266-zmpt101b-true-rms-voltage-dashboard
// Parts used: https://shillehtek.com/products/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi
//             https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
//             https://shillehtek.com/products/shillehtek-universal-power-supply-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Filters.h>

float testFrequency = 50;                    // your mains frequency (Hz)
float windowLength = 100.0 / testFrequency;  // sample window; 40/f on 5V Arduinos
int sensorPin = A0;

double intercept = 0;   // set after the zero-volt test
double slope = 1;       // set after the multimeter comparison
double currentVolts;

unsigned long printPeriod = 1000;
unsigned long previousMillis = 0;

RunningStatistics inputStats;

void setup() {
  Serial.begin(115200);
  inputStats.setWindowSecs(windowLength);
}

void loop() {
  inputStats.input(analogRead(sensorPin));   // sample continuously

  if (millis() - previousMillis >= printPeriod) {
    previousMillis = millis();
    currentVolts = intercept + slope * inputStats.sigma();
    Serial.print("Voltage: ");
    Serial.println(currentVolts, 1);
  }
}
