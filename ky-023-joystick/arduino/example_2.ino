// Reads analog axes, applies a center deadzone, converts the analog position into discrete directions (UP/DOWN/LEFT/RIGHT/CENTER), and prints the result to Serial.
//
// Buy this module: https://shillehtek.com/products/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// Convert joystick to discrete directions with a center deadzone

const int xPin = A0;
const int yPin = A1;
const int center = 512;
const int deadzone = 80;

void setup() { Serial.begin(9600); }

void loop() {
  int x = analogRead(xPin) - center;
  int y = analogRead(yPin) - center;

  if (abs(x) < deadzone && abs(y) < deadzone) {
    Serial.println("CENTER");
  } else if (abs(x) > abs(y)) {
    Serial.println(x > 0 ? "RIGHT" : "LEFT");
  } else {
    Serial.println(y > 0 ? "DOWN" : "UP");
  }
  delay(150);
}
