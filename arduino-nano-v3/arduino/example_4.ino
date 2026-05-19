// Read an analog value from A0, compute the voltage assuming a 5 V reference, and print the raw 10‑bit value and voltage.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-presoldered-ch340g-atmega328p-manual
// More examples: https://github.com/shillehtek/examples
//

// Read an analog value from A0 (potentiometer, LDR, etc.)
// and print both the raw 10-bit value (0-1023) and the voltage.

const int SENSOR_PIN = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("Analog Read on A0");
}

void loop() {
  int rawValue = analogRead(SENSOR_PIN);
  float voltage = rawValue * (5.0 / 1023.0);

  Serial.print("Raw: ");
  Serial.print(rawValue);
  Serial.print("  Voltage: ");
  Serial.print(voltage, 3);
  Serial.println(" V");

  delay(200);
}
