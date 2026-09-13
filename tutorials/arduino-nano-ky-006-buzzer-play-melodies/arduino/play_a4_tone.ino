// Plays a single 440 Hz (A4) tone for one second on a KY-006 buzzer connected to pin 8 using tone() in setup().
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ky-006-buzzer-play-melodies
// Parts used: https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int BUZZER = 8;

void setup() {
  tone(BUZZER, 440, 1000);   // 440 Hz (A4) for 1 second
}

void loop() {}
