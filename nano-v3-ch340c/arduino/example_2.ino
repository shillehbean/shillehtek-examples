// Send an incrementing counter to the USB serial monitor at 9600 baud.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Print a counter over USB Serial
// Open Serial Monitor at 9600 baud to see output

unsigned long counter = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect (needed on some boards)
  }
  Serial.println("Arduino Nano V3.0 ready!");
}

void loop() {
  Serial.print("Counter: ");
  Serial.println(counter);
  counter++;
  delay(500);
}
