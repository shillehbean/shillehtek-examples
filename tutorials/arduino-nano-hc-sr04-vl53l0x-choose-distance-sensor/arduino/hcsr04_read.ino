// Triggers the HC-SR04 ultrasonic sensor, measures echo pulse width, converts to centimeters, and prints distance to the Serial console.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-hc-sr04-vl53l0x-choose-distance-sensor
// Parts used: https://shillehtek.com/products/shillehtek-hc-sr04-with-rgb-light-distance
//             https://shillehtek.com/products/gy-vl53l0xv2-laser-ranging-tof-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// HC-SR04
#define TRIG 9
#define ECHO 10

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long dur = pulseIn(ECHO, HIGH);
  float cm = dur * 0.0343 / 2;
  Serial.println(cm);
  delay(50);
}

// VL53L0X (Pololu library)
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X tof;

void setup() {
  Wire.begin();
  tof.init();
  tof.setTimeout(500);
  tof.startContinuous();
}

void loop() {
  Serial.println(tof.readRangeContinuousMillimeters());
}
