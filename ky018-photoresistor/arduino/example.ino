// Reads the KY-018 analog output on A0 with an Arduino, prints the raw 0–1023 light level over serial, and classifies it as bright/dim/dark.
//
// Buy this module: https://shillehtek.com/products/photoresistor-light-sensor-ky-018-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/photoresistor-light-sensor-ky-018-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// KY-018 Photoresistor - Arduino Example
// S -> A0, VCC (middle) -> 5V, - -> GND

const int sensorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(sensorPin);   // 0-1023, higher = brighter

  Serial.print("Light level: ");
  Serial.print(raw);

  if (raw > 700) {
    Serial.println("  (bright)");
  } else if (raw > 300) {
    Serial.println("  (dim)");
  } else {
    Serial.println("  (dark)");
    // Example action: digitalWrite(LED_BUILTIN, HIGH);  // night light on
  }

  delay(500);
}
