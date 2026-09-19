// Uses PWM on pin 9 to smoothly fade an external LED in and out by varying duty cycle with analogWrite.
//
// Buy this module: https://shillehtek.com/products/arduino-uno-r3-starter-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-uno-r3-starter-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// LED + 220 ohm resistor on pin 9 (a PWM pin, marked with ~)
const int LED = 9;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  for (int b = 0; b <= 255; b += 5) {   // brighten
    analogWrite(LED, b);
    delay(20);
  }
  for (int b = 255; b >= 0; b -= 5) {   // dim
    analogWrite(LED, b);
    delay(20);
  }
}
