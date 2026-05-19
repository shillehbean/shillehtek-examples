// Reads both left and right joystick X/Y axes plus their push buttons and prints the raw values and button states to the serial monitor.
//
// Buy this module: https://shillehtek.com/products/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3-manual
// More examples: https://github.com/shillehtek/examples
//

// Joystick Shield V1.A - Read both joysticks
// Print X, Y, and button state for left and right sticks

const int LX = A0, LY = A1, LBTN = 8;
const int RX = A2, RY = A3, RBTN = 9;

void setup() {
  Serial.begin(9600);
  pinMode(LBTN, INPUT_PULLUP);
  pinMode(RBTN, INPUT_PULLUP);
}

void loop() {
  int lx = analogRead(LX), ly = analogRead(LY);
  int rx = analogRead(RX), ry = analogRead(RY);
  bool lpress = digitalRead(LBTN) == LOW;
  bool rpress = digitalRead(RBTN) == LOW;

  Serial.print("L: ("); Serial.print(lx); Serial.print(",");
  Serial.print(ly); Serial.print(") "); Serial.print(lpress ? "DOWN" : "up");
  Serial.print("   R: ("); Serial.print(rx); Serial.print(",");
  Serial.print(ry); Serial.print(") "); Serial.println(rpress ? "DOWN" : "up");

  delay(100);
}
