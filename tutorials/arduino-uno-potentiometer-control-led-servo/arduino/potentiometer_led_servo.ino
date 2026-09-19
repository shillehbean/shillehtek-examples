// Reads a potentiometer on A0 and maps the value to control LED PWM on pin 9 and a servo angle on pin 10 while printing readings to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-potentiometer-control-led-servo
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

const int POT = A0, LED = 9, SERVO_PIN = 10;
Servo knobServo;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  knobServo.attach(SERVO_PIN);
}

void loop() {
  int raw = analogRead(POT);                     // 0-1023

  int brightness = map(raw, 0, 1023, 0, 255);    // LED dimmer
  analogWrite(LED, brightness);

  int angle = map(raw, 0, 1023, 0, 180);         // servo position
  knobServo.write(angle);

  Serial.print(raw); Serial.print(" -> LED ");
  Serial.print(brightness); Serial.print(", servo ");
  Serial.println(angle);
  delay(20);
}
