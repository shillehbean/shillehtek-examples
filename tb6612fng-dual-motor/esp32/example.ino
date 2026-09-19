// Run a motor attached to Motor A on an ESP32 by fixing direction pins for forward rotation and using PWM on PWMA to ramp the motor speed up and down in a loop.
//
// Buy this module: https://shillehtek.com/products/tb6612fng-dual-motor-driver-module-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tb6612fng-dual-motor-driver-module-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int PWMA = 25, AIN1 = 26, AIN2 = 27, STBY = 33;

void setup() {
  pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(STBY, OUTPUT); pinMode(PWMA, OUTPUT);
  digitalWrite(STBY, HIGH);
  digitalWrite(AIN1, HIGH);   // forward
  digitalWrite(AIN2, LOW);
}

void loop() {
  for (int d = 0; d <= 255; d += 5) {   // ramp up
    analogWrite(PWMA, d);
    delay(40);
  }
  for (int d = 255; d >= 0; d -= 5) {   // ramp down
    analogWrite(PWMA, d);
    delay(40);
  }
}
