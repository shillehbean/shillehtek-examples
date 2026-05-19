// Cycles a MOSFET-driven mist maker on D3 for 5 seconds and off for 55 seconds to produce a single 'puff' per minute using an Arduino.
//
// Buy this module: https://shillehtek.com/products/dc-5v-ultrasonic-mist-maker-humidifier-module-108khz-usb
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dc-5v-ultrasonic-mist-maker-humidifier-module-108khz-usb-manual
// More examples: https://github.com/shillehtek/examples
//

// DC 5V Mist Maker - cycle on/off via a MOSFET on D3
// 5 seconds on, 55 seconds off (a "puff" every minute)

const int mistPin = 3;

void setup() {
  pinMode(mistPin, OUTPUT);
  digitalWrite(mistPin, LOW);
}

void loop() {
  digitalWrite(mistPin, HIGH);   // turn the mist maker on
  delay(5000);
  digitalWrite(mistPin, LOW);    // turn it off
  delay(55000);
}
