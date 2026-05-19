// Read the jack's mechanical detect switch and print "Plug INSERTED" or "Plug REMOVED" over Serial at 9600 baud.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board-manual
// More examples: https://github.com/shillehtek/examples
//

// 3.5mm Audio Jack Breakout - Detect when a plug is inserted

const int detectPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(detectPin, INPUT_PULLUP);
}

void loop() {
  bool plugged = (digitalRead(detectPin) == LOW);
  Serial.println(plugged ? "Plug INSERTED" : "Plug REMOVED");
  delay(200);
}
