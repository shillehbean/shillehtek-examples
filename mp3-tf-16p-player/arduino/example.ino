// Arduino sketch that uses SoftwareSerial and the DFRobotDFPlayerMini library to initialize the player, set volume, play 0001.mp3 on startup, and advance to the next track every 10 seconds.
//
// Buy this module: https://shillehtek.com/products/mp3-player-module-tf-card-arduino-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mp3-player-module-tf-card-arduino-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MP3-TF-16P / DFPlayer Mini - Arduino Example
// TX->D10, RX->D11 via 1k | Library: "DFRobotDFPlayerMini"

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

SoftwareSerial mp3Serial(10, 11);   // RX, TX
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(115200);
  mp3Serial.begin(9600);

  if (!player.begin(mp3Serial)) {
    Serial.println("DFPlayer not responding - check card and wiring");
    while (1);
  }
  player.volume(20);            // 0-30
  player.play(1);               // play 0001.mp3
  Serial.println("Playing track 1");
}

void loop() {
  // next track every 10 seconds as a demo
  delay(10000);
  player.next();
  Serial.println("Next track");
}
