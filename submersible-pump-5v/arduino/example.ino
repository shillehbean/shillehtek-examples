// Controls a 5V submersible pump via a MOSFET on pin D9 and uses an analog soil moisture sensor on A0 to run a 4s watering cycle when the reading exceeds the configured dry threshold (or falls back to a simple timer when USE_SENSOR is false).
//
// Buy this module: https://shillehtek.com/products/mini-submersible-water-pump-5v-120lph-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-submersible-water-pump-5v-120lph-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 5V 120L/H pump on MOSFET, gate on D9.
// Waters when the analog moisture reading is too dry.
// No sensor? Set USE_SENSOR to false for a simple timer.

const int  PUMP_PIN   = 9;
const int  SENSOR_PIN = A0;
const bool USE_SENSOR = true;
const int  DRY_LEVEL  = 600;   // calibrate for your sensor

void setup() {
  pinMode(PUMP_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  bool shouldWater = true;

  if (USE_SENSOR) {
    int m = analogRead(SENSOR_PIN);
    Serial.print("Moisture: ");
    Serial.println(m);
    shouldWater = (m > DRY_LEVEL);   // higher = drier for many sensors
  }

  if (shouldWater) {
    digitalWrite(PUMP_PIN, HIGH);
    delay(4000);                     // 4 s water shot
    digitalWrite(PUMP_PIN, LOW);
  }
  delay(60000);                      // check every minute
}
