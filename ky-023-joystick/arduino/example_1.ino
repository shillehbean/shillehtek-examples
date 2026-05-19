// Reads the joystick's X and Y analog axes and the push switch, then prints raw values and switch state to the Serial monitor at 9600 baud.
//
// Buy this module: https://shillehtek.com/products/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// KY-023 joystick on Arduino
// VRX -> A0, VRY -> A1, SW -> D2, +5V, GND

const int xPin = A0;
const int yPin = A1;
const int swPin = 2;

void setup() {
  pinMode(swPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(xPin);     // 0 - 1023
  int y = analogRead(yPin);     // 0 - 1023
  int sw = digitalRead(swPin);  // 0 = pressed

  Serial.print("X: "); Serial.print(x);
  Serial.print(" Y: "); Serial.print(y);
  Serial.print(" SW: "); Serial.println(sw == LOW ? "PRESSED" : "released");

  delay(100);
}
