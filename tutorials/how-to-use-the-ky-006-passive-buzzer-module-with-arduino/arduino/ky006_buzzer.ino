// Plays two short tones on a KY-006 passive buzzer by toggling digital pin 8 with different pulse widths.
//
// Full tutorial: https://shillehtek.com/blogs/news/how-to-use-the-ky-006-passive-buzzer-module-with-arduino
// Parts used: https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
//             https://shillehtek.com/products/shillehtek-400-point-breadboard
// More examples: https://github.com/shillehbean/shillehtek-examples
//

int buzzer = 8; // set the buzzer control digital IO pin

void setup() {
  pinMode(buzzer, OUTPUT); // set pin 8 as output
}

void loop() {
  for (int i = 0; i < 100; i++) {  // make a sound
    digitalWrite(buzzer, HIGH); // send high signal to buzzer
    delay(1); // delay 1ms
    digitalWrite(buzzer, LOW); // send low signal to buzzer
    delay(1);
  }

  delay(50);

  for (int j = 0; j < 100; j++) { // make another sound
    digitalWrite(buzzer, HIGH);
    delay(2); // delay 2ms
    digitalWrite(buzzer, LOW);
    delay(2);
  }

  delay(500);
}
