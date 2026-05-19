// Read a 10-bit analog value from A0, convert it to voltage (0–5V), and print raw and voltage readings over Serial.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Read an analog value from A0 (e.g., potentiometer, LDR, analog sensor)
// Convert the 10-bit reading (0-1023) to a voltage (0-5V)

const int SENSOR_PIN = A0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
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
