// Reads and smooths the potentiometer value on A0, maps it to percent and PWM, dims an LED on D9, and prints raw/percent values over serial.
//
// Buy this module: https://shillehtek.com/products/slide-potentiometer-module-10k-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/slide-potentiometer-module-10k-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 10K Slide Potentiometer - Arduino Example
// OTA->A0, VCC->5V, GND->GND, optional LED on D9

const int potPin = A0;
const int ledPin = 9;          // PWM pin

int readSmooth() {
  long total = 0;
  for (int i = 0; i < 16; i++) total += analogRead(potPin);
  return total / 16;
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println("Slide the fader!");
}

void loop() {
  int raw = readSmooth();                 // 0..1023
  int percent = map(raw, 0, 1023, 0, 100);
  int pwm = map(raw, 0, 1023, 0, 255);

  analogWrite(ledPin, pwm);               // slider dims the LED

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print(" | Position: ");
  Serial.print(percent);
  Serial.println(" %");
  delay(100);
}
