// Powers the probe from a digital pin, reads the analog value on A0 to determine dry/low/high water conditions, and prints the result every 3 seconds.
//
// Buy this module: https://shillehtek.com/products/sensor-rain-water-level-arduino-raspberry-pi-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sensor-rain-water-level-arduino-raspberry-pi-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Water Level Sensor - Arduino Example (GPIO-powered to prevent corrosion)
// S -> A0, + -> D7, - -> GND

const int powerPin = 7;
const int sensorPin = A0;

void setup() {
  Serial.begin(9600);
  pinMode(powerPin, OUTPUT);
  digitalWrite(powerPin, LOW);    // sensor off between readings
}

int readLevel() {
  digitalWrite(powerPin, HIGH);   // energize the probe
  delay(20);                      // let the reading settle
  int value = analogRead(sensorPin);
  digitalWrite(powerPin, LOW);    // power off - no electrolysis
  return value;
}

void loop() {
  int level = readLevel();        // 0-1023

  Serial.print("Raw: ");
  Serial.print(level);

  if (level < 100) {
    Serial.println("  (dry)");
  } else if (level < 450) {
    Serial.println("  (low water)");
  } else {
    Serial.println("  (HIGH water!)");
    // trigger your pump/alarm/notification here
  }

  delay(3000);                    // check every 3 seconds
}
