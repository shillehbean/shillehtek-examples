// Blink test sketch for an Arduino Pro Mini uploaded via the FT232RL; toggles the LED on pin 13 and prints a startup message over serial.
//
// Buy this module: https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs-manual
// More examples: https://github.com/shillehtek/examples
//

// Blink sketch for Arduino Pro Mini, uploaded via FT232RL
// Steps in Arduino IDE:
//  1. Tools -> Board: Arduino Pro or Pro Mini
//  2. Tools -> Processor: ATmega328P (5V, 16 MHz) or (3.3V, 8 MHz)
//  3. Tools -> Port: select the FT232RL COM/tty port
//  4. Click Upload

const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  Serial.println("Pro Mini online via FT232RL");
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
