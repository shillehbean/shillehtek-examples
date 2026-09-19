// ESP32 example using Serial2 to communicate with the DFPlayer and a BOOT button (GPIO0) to play a random track from a numbered set of MP3 files.
//
// Buy this module: https://shillehtek.com/products/mp3-player-module-tf-card-arduino-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mp3-player-module-tf-card-arduino-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MP3-TF-16P - ESP32 sound-effect trigger
// TX->GPIO16, RX->GPIO17 via 1k, button GPIO 0 (BOOT) plays a random clip

#include <DFRobotDFPlayerMini.h>

DFRobotDFPlayerMini player;
const int NUM_TRACKS = 5;          // 0001.mp3 .. 0005.mp3 on the card

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  pinMode(0, INPUT_PULLUP);

  if (!player.begin(Serial2)) {
    Serial.println("DFPlayer not responding");
    while (1) delay(10);
  }
  player.volume(22);
  Serial.println("Press BOOT for a random sound");
}

void loop() {
  if (digitalRead(0) == LOW) {
    int track = random(1, NUM_TRACKS + 1);
    player.play(track);
    Serial.printf("Playing %04d.mp3\n", track);
    delay(400);                    // debounce
  }
}
