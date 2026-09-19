// Reads the analog IR intensity on A0 and the comparator digital output on D2, printing raw values and a flame/no-flame message over Serial.
//
// Buy this module: https://shillehtek.com/products/flame-sensor-ky-026-arduino-esp32-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/flame-sensor-ky-026-arduino-esp32-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// KY-026 Flame Sensor - Arduino Example
// A0 -> A0, D0 -> Digital Pin 2, + -> 5V, G -> GND

const int analogPin = A0;   // analog IR intensity
const int digitalPin = 2;   // comparator flame output

void setup() {
  Serial.begin(9600);
  pinMode(digitalPin, INPUT);
}

void loop() {
  // Read raw IR intensity (0-1023)
  int analogValue = analogRead(analogPin);

  // Read the comparator output: HIGH = flame above threshold
  int flameState = digitalRead(digitalPin);

  Serial.print("Analog: ");
  Serial.print(analogValue);

  if (flameState == HIGH) {
    Serial.println("  |  FLAME DETECTED!");
  } else {
    Serial.println("  |  No flame");
  }

  // Watch the analog value with and without a flame to learn
  // your board's baseline, then adjust the potentiometer so
  // D0 triggers exactly when you want it to.
  delay(500);
}
