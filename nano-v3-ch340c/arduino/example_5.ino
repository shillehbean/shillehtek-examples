// Create a fading (breathing) effect by PWMing an LED on pin D9 with analogWrite.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Fade an LED in and out using PWM
// Connect an LED (with 220 ohm resistor) from D9 to GND
// D9 is one of the PWM-capable pins (marked with ~ on the silkscreen)

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
