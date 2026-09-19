// Reads an analog value from a potentiometer on A0, converts it to a voltage, and prints raw and voltage readings to Serial at 9600 baud.
//
// Buy this module: https://shillehtek.com/products/arduino-uno-r3-starter-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-uno-r3-starter-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Potentiometer: outer legs to 5V and GND, middle leg to A0
// Open Tools > Serial Plotter at 9600 baud and turn the knob
void setup() {
  Serial.begin(9600);
}

void loop() {
  int raw = analogRead(A0);              // 0-1023
  float volts = raw * (5.0 / 1023.0);
  Serial.print("raw:");
  Serial.print(raw);
  Serial.print("\tvolts:");
  Serial.println(volts);
  delay(50);
}
