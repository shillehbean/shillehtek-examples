// Arduino/ESP32 sketch that ramps a DC motor forward, applies a brake, then ramps it in reverse using PWM on the DRV8871 IN pins.
//
// Buy this module: https://shillehtek.com/products/drv8871-h-bridge-motor-driver-module-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/drv8871-h-bridge-motor-driver-module-pre-soldered-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// DRV8871 motor driver - ramp a DC motor forward, brake, then ramp it in reverse
// Arduino Uno/Nano: IN1 = D9, IN2 = D10, GND = GND.  ESP32: IN1 = GPIO 25, IN2 = GPIO 26, GND = GND.
// The motor supply (6.5 V to 45 V) goes to POWER + and POWER -. Leave the header VM pin unconnected.
#if defined(ESP32)
const int PIN_IN1 = 25;
const int PIN_IN2 = 26;
#else
const int PIN_IN1 = 9;
const int PIN_IN2 = 10;
#endif

void drive(int speed) {              // speed: -255 (full reverse) to 255 (full forward)
  if (speed >= 0) {
    analogWrite(PIN_IN1, speed);
    analogWrite(PIN_IN2, 0);
  } else {
    analogWrite(PIN_IN1, 0);
    analogWrite(PIN_IN2, -speed);
  }
}

void brake() {                       // both inputs HIGH = brake
  analogWrite(PIN_IN1, 255);
  analogWrite(PIN_IN2, 255);
}

void setup() {
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  drive(0);                          // both inputs LOW = coast
}

void loop() {
  for (int s = 0; s <= 255; s += 5) { drive(s); delay(20); }      // speed up forward
  delay(1000);
  brake();
  delay(500);
  for (int s = 0; s >= -255; s -= 5) { drive(s); delay(20); }     // speed up in reverse
  delay(1000);
  drive(0);                          // coast to a stop
  delay(2000);
}
