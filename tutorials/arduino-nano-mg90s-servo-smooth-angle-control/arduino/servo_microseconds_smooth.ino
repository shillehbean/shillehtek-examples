// Smoothly sweep a servo by gradually adjusting the pulse width (microseconds) and sending pulses with Servo.writeMicroseconds() for finer control.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mg90s-servo-smooth-angle-control
// Parts used: https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "Servo.h"

#define SERVO1_PIN 9

#define MIN_MS 0
#define MAX_MS 2000
#define DEFAULT_MS 1000

int servoPulse = DEFAULT_MS;

Servo Servo1;

void setup()
{
  Servo1.attach(SERVO1_PIN);
  Servo1.writeMicroseconds(DEFAULT_MS);
}

void loop()
{
  graduallyApplyServoPulse(MAX_MS);
  delay(1000);

  graduallyApplyServoPulse(MIN_MS);
  delay(1000);
}

void graduallyApplyServoPulse(int pulse)
{
  int limitedPulse = limitServoPulse(pulse);

  while (servoPulse != limitedPulse) {
    if (servoPulse > limitedPulse) {
      servoPulse--;
    }

    if (servoPulse < limitedPulse) {
      servoPulse++;
    }

    Servo1.writeMicroseconds(servoPulse);
  }
}

int limitServoPulse(int pulse)
{
  return constrain(pulse, MIN_MS, MAX_MS);
}
