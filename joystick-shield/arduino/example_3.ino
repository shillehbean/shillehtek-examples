// Converts the left joystick's analog X/Y into a discrete direction (LEFT/RIGHT/UP/DOWN/CENTER) using a deadzone and prints the result to serial.
//
// Buy this module: https://shillehtek.com/products/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3-manual
// More examples: https://github.com/shillehtek/examples
//

// Convert raw joystick X/Y into discrete UP/DOWN/LEFT/RIGHT

const int LX = A0, LY = A1;
const int CENTER = 512, DEAD = 100;

const char* dirOf(int x, int y) {
  if (x < CENTER - DEAD) return "LEFT";
  if (x > CENTER + DEAD) return "RIGHT";
  if (y < CENTER - DEAD) return "UP";
  if (y > CENTER + DEAD) return "DOWN";
  return "CENTER";
}

void setup() { Serial.begin(9600); }

void loop() {
  Serial.println(dirOf(analogRead(LX), analogRead(LY)));
  delay(150);
}
