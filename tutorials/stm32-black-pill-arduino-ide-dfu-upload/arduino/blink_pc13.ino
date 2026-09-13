// Blink the onboard LED (PC13) on the STM32F411 Black Pill with a 100 ms on/off interval.
//
// Full tutorial: https://shillehtek.com/blogs/news/stm32-black-pill-arduino-ide-dfu-upload
// Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f411ceu6
// More examples: https://github.com/shillehbean/shillehtek-examples
//

/* Blink onboard LED at 0.1 second interval */

void setup() {
  // initialize digital pin PC13 as an output
  pinMode(PC13, OUTPUT);  // LED connected to pin PC13
}

void loop() {
  digitalWrite(PC13, HIGH);   // turn the LED on
  delay(100);                 // wait for 100ms
  digitalWrite(PC13, LOW);    // turn the LED off
  delay(100);                 // wait for 100ms
}
