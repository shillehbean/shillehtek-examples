// Fade an LED connected to D9 using PWM by incrementing and reversing the duty cycle to create a smooth fade in/out.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-presoldered-ch340g-atmega328p-manual
// More examples: https://github.com/shillehtek/examples
//

// Fade an LED in and out using PWM.
// Wire an LED (with a 220 ohm resistor) from D9 to GND.
// D9 is one of six PWM pins (marked with "~" on the silkscreen).

const int LED_PIN = 9;
int brightness = 0;
int fadeStep = 5;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  analogWrite(LED_PIN, brightness);

  brightness += fadeStep;
  if (brightness <= 0 || brightness >= 255) {
    fadeStep = -fadeStep;  // Reverse direction at endpoints
  }

  delay(20);
}
