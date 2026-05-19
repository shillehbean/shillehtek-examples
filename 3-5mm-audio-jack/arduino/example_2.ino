// Sample an electret microphone AC-coupled through the TRRS jack, compute a simple RMS-like level from multiple analog reads, and print the audio level over Serial.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board-manual
// More examples: https://github.com/shillehtek/examples
//

// Read electret mic from a TRRS headset
// Wire: RING2 -> 2.2k pull-up to 5V, then RING2 -> 0.1uF cap -> A0
// SLEEVE -> GND. The capacitor blocks the DC bias; A0 reads the AC audio.

const int micPin = A0;
const int samples = 64;

void setup() {
  Serial.begin(115200);
}

void loop() {
  long sum = 0;
  long sumSq = 0;
  for (int i = 0; i < samples; i++) {
    int v = analogRead(micPin);
    sum += v;
    sumSq += (long)v * v;
  }
  long mean = sum / samples;
  long rms = sqrt((sumSq / samples) - (mean * mean));
  Serial.println(rms);
  delay(20);
}
