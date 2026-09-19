// Arduino sketch that reads the SW-520D on digital pin 2 with debounce and prints "TILTED!" or "Level again" to Serial.
//
// Buy this module: https://shillehtek.com/products/tilt-switch-sw-520d-vibration-sensor
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tilt-switch-sw-520d-vibration-sensor-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// SW-520D Tilt Switch Module - Arduino Example (debounced)
// D0->D2, VCC->5V, GND->GND

const int tiltPin = 2;
const unsigned long DEBOUNCE_MS = 60;

int stableState;
int lastReading;
unsigned long lastChange = 0;

void setup() {
  Serial.begin(9600);
  pinMode(tiltPin, INPUT);
  stableState = lastReading = digitalRead(tiltPin);
  Serial.println("Tilt sensor ready - tip me over!");
}

void loop() {
  int reading = digitalRead(tiltPin);

  if (reading != lastReading) {
    lastChange = millis();          // edge seen - restart timer
    lastReading = reading;
  }

  if (millis() - lastChange > DEBOUNCE_MS && reading != stableState) {
    stableState = reading;
    if (stableState == HIGH) {
      Serial.println("TILTED!");
    } else {
      Serial.println("Level again");
    }
  }
}
