// Samples the ZMPT101B on Arduino A0, computes the RMS voltage from ADC samples over a time window, and prints the AC voltage to Serial.
//
// Buy this module: https://shillehtek.com/products/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int SENSOR_PIN = A0;
float CAL = 250.0;   // scale factor - tune against a multimeter

void setup() {
  Serial.begin(9600);
}

void loop() {
  const unsigned long windowMs = 200;  // 10 cycles @ 50 Hz, 12 @ 60 Hz
  unsigned long start = millis();
  unsigned long n = 0;
  double sum = 0, sumSq = 0;

  while (millis() - start < windowMs) {
    int raw = analogRead(SENSOR_PIN);
    sum += raw;
    sumSq += (double)raw * raw;
    n++;
  }

  double mean = sum / n;                       // DC bias (~512)
  double variance = sumSq / n - mean * mean;
  double rmsCounts = sqrt(variance > 0 ? variance : 0);
  double volts = rmsCounts * (5.0 / 1023.0) * CAL;

  Serial.print("AC voltage: ");
  Serial.print(volts, 1);
  Serial.println(" V");
  delay(500);
}
