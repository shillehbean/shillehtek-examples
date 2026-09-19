// A bench-test Arduino sketch that toggles the motor driver pins to spin the left and right wheel pairs forward and reverse so you can verify wheel direction and wiring.
//
// Buy this module: https://shillehtek.com/products/esp32-cam-4wd-robot-car-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-cam-4wd-robot-car-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Bench test with the car's wheels OFF the ground.
// Match these pins to your driver wiring (Motor Wiring tab).
const int L_FWD = 12, L_REV = 13;   // left pair
const int R_FWD = 14, R_REV = 15;   // right pair

void setup() {
  pinMode(L_FWD, OUTPUT); pinMode(L_REV, OUTPUT);
  pinMode(R_FWD, OUTPUT); pinMode(R_REV, OUTPUT);
}

void allStop() {
  digitalWrite(L_FWD, LOW); digitalWrite(L_REV, LOW);
  digitalWrite(R_FWD, LOW); digitalWrite(R_REV, LOW);
}

void loop() {
  // forward - all four wheels should spin the same way
  digitalWrite(L_FWD, HIGH); digitalWrite(R_FWD, HIGH);
  delay(1500);
  allStop(); delay(500);

  // spin in place - left pair back, right pair forward
  digitalWrite(L_REV, HIGH); digitalWrite(R_FWD, HIGH);
  delay(1500);
  allStop(); delay(1500);
  // Any wheel turning the wrong way: swap that motor's two leads.
}
