// Plays alternating 1 kHz and 2 kHz tones on a passive buzzer attached to digital pin 8, with a short silent pause between cycles.
//
// Buy this module: https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects-manual
// More examples: https://github.com/shillehtek/examples
//

// KY-006 Passive Buzzer - alternating two-tone beep on Arduino
// Wire S to D8, +Vin to 5V, - to GND

const int buzzerPin = 8;

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  tone(buzzerPin, 1000);   // 1 kHz tone
  delay(250);
  tone(buzzerPin, 2000);   // 2 kHz tone
  delay(250);
  noTone(buzzerPin);       // silence
  delay(500);
}
