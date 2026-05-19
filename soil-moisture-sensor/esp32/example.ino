// Powers the sensor from a GPIO to limit corrosion, reads and averages ADC samples from AO on the ESP32, maps the reading to a moisture percentage, and prints results (once per minute).
//
// Buy this module: https://shillehtek.com/products/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32 - power the soil sensor only while reading, to slow corrosion
// VCC -> GPIO 5 (switched);  AO -> GPIO 34;  DO -> GPIO 35

const int powerPin = 5;
const int aoPin    = 34;
const int doPin    = 35;

const int DRY_VAL = 3300;
const int WET_VAL = 1300;

void setup() {
  Serial.begin(115200);
  pinMode(powerPin, OUTPUT);
  pinMode(doPin, INPUT);
  analogReadResolution(12);
}

int readSoil() {
  digitalWrite(powerPin, HIGH);
  delay(200);                       // settle time
  long sum = 0;
  for (int i = 0; i < 20; i++) { sum += analogRead(aoPin); delay(5); }
  digitalWrite(powerPin, LOW);
  return sum / 20;
}

void loop() {
  int raw = readSoil();
  int pct = map(raw, DRY_VAL, WET_VAL, 0, 100);
  pct = constrain(pct, 0, 100);
  Serial.printf("Raw=%4d  Moisture=%3d %%\n", raw, pct);
  delay(60000);                     // once a minute is plenty
}
