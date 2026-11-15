// Arduino-framework example (works on ESP32 or AVR Arduino) that uses microsecond pulses to spin the FS90R clockwise, stop, then counterclockwise with delays between actions.
//
// Buy this module: https://shillehtek.com/products/fs90r-micro-servo-continuous-rotation
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/fs90r-micro-servo-continuous-rotation-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// FS90R continuous rotation servo - spin one way, stop, spin the other way, stop
// Wiring: orange = signal (D9 on Arduino, GPIO 18 on ESP32), red = 5 V, brown = GND
// ESP32 needs the ESP32Servo library; Arduino boards use the built-in Servo library.
#if defined(ESP32)
#include <ESP32Servo.h>
const int SERVO_PIN = 18;
#else
#include <Servo.h>
const int SERVO_PIN = 9;
#endif

const int STOP_US = 1500;          // change by a few microseconds if the servo creeps at stop

Servo servo;

void setup() {
  servo.attach(SERVO_PIN);
  servo.writeMicroseconds(STOP_US);
}

void loop() {
  servo.writeMicroseconds(STOP_US - 200);   // clockwise; go further from 1500 for more speed
  delay(2000);
  servo.writeMicroseconds(STOP_US);         // stop
  delay(1000);
  servo.writeMicroseconds(STOP_US + 200);   // counterclockwise
  delay(2000);
  servo.writeMicroseconds(STOP_US);         // stop
  delay(1000);
}
