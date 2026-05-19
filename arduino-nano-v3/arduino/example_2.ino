// Send an incrementing counter over USB serial at 9600 baud, updating every 500 ms.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-presoldered-ch340g-atmega328p-manual
// More examples: https://github.com/shillehtek/examples
//

// Print a counter over USB serial.
// Open Serial Monitor at 9600 baud to see output.

unsigned long counter = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Nano V3.0 ready!");
}

void loop() {
  Serial.print("Counter: ");
  Serial.println(counter);
  counter++;
  delay(500);
}
