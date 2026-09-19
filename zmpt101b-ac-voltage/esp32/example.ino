// Configures the ESP32 ADC (pin 34) with 11 dB attenuation, collects ADC samples to compute RMS of the AC waveform, converts to volts and prints the result over Serial.
//
// Buy this module: https://shillehtek.com/products/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int SENSOR_PIN = 34;   // ADC1 input-only pin
float CAL = 250.0;           // tune against a multimeter

void setup() {
  Serial.begin(115200);
  analogSetPinAttenuation(SENSOR_PIN, ADC_11db);  // full 0-3.3 V range
}

void loop() {
  const unsigned long windowMs = 200;
  unsigned long start = millis();
  unsigned long n = 0;
  double sum = 0, sumSq = 0;

  while (millis() - start < windowMs) {
    int raw = analogRead(SENSOR_PIN);   // 0-4095
    sum += raw;
    sumSq += (double)raw * raw;
    n++;
  }

  double mean = sum / n;
  double variance = sumSq / n - mean * mean;
  double rmsCounts = sqrt(variance > 0 ? variance : 0);
  double volts = rmsCounts * (3.3 / 4095.0) * CAL;

  Serial.printf("AC voltage: %.1f V\n", volts);
  delay(500);
}
