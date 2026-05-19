// Reads a button on D3 and sends the string "Hello from XIAO!" plus Enter over the native USB HID keyboard when the button is pressed.
//
// Buy this module: https://shillehtek.com/products/seeeduino-xiao-samd21-arduino-board-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/seeeduino-xiao-samd21-arduino-board-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// Seeeduino XIAO SAMD21 - Send keystrokes over native USB HID
// Wire a button between D3 and GND

#include <Keyboard.h>

const int buttonPin = 3;   // D3
bool lastState = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  bool state = digitalRead(buttonPin);
  if (state == LOW && lastState == HIGH) {
    Keyboard.print("Hello from XIAO!");
    Keyboard.write(KEY_RETURN);
    delay(50);   // simple debounce
  }
  lastState = state;
}
