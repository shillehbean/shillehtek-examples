// Reads a pushbutton using the internal pull-up on pin 2 and turns an LED on pin 8 on while the button is pressed.
//
// Buy this module: https://shillehtek.com/products/arduino-uno-r3-starter-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-uno-r3-starter-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int BUTTON = 2;   // to GND, using the internal pull-up
const int LED = 8;

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);  // reads HIGH until pressed
  pinMode(LED, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON) == LOW) {   // LOW = pressed
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }
}
