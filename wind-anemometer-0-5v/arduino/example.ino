// Reads the anemometer's 0–5V analog signal on A0, averages samples, converts the measured voltage to wind speed (m/s and mph), and prints results over Serial.
//
// Buy this module: https://shillehtek.com/products/anemometer-wind-speed-0-5v-analog-output
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/anemometer-wind-speed-0-5v-analog-output-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Wind Speed Sensor (0-5V Anemometer) - Arduino Example
// Blue signal -> A0 (direct), Brown -> 12V supply, Black -> GND (shared)
// Wind speed (m/s) = Vout x 6   (5V = 30 m/s)

const int windPin = A0;
const int numSamples = 16;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Average several readings to steady the value in gusty air
  long total = 0;
  for (int i = 0; i < numSamples; i++) {
    total += analogRead(windPin);
    delay(5);
  }
  float raw = total / (float)numSamples;

  // Convert the 10-bit reading (0-1023) to volts (5V reference)
  float volts = raw * (5.0 / 1023.0);

  // Convert volts to wind speed
  float windMs = volts * 6.0;         // meters per second
  float windMph = windMs * 2.237;     // miles per hour

  Serial.print("Signal: ");
  Serial.print(volts, 2);
  Serial.print(" V | Wind: ");
  Serial.print(windMs, 1);
  Serial.print(" m/s (");
  Serial.print(windMph, 1);
  Serial.println(" mph)");

  delay(1000);
}
