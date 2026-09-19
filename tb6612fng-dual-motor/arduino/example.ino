// Control a single DC motor (Motor A) with the TB6612FNG from an Arduino: set direction via two digital pins, apply PWM for speed, and demonstrate forward, reverse, and short braking sequences.
//
// Buy this module: https://shillehtek.com/products/tb6612fng-dual-motor-driver-module-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tb6612fng-dual-motor-driver-module-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int PWMA = 5, AIN1 = 4, AIN2 = 3, STBY = 6;

void setup() {
  pinMode(PWMA, OUTPUT); pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT); pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);         // enable the driver!
}

void motorA(int speed) {            // speed: -255..255
  digitalWrite(AIN1, speed >= 0);
  digitalWrite(AIN2, speed < 0);
  analogWrite(PWMA, abs(speed));
}

void brakeA() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, HIGH);         // short brake
  analogWrite(PWMA, 0);
}

void loop() {
  motorA(200);   delay(2000);       // forward ~80%
  motorA(-120);  delay(2000);       // reverse ~47%
  brakeA();      delay(1000);
}
