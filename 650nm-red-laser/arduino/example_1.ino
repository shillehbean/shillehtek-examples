// Blinks the laser on and off every 500 ms by switching an NPN transistor connected to Arduino digital pin D9.
//
// Buy this module: https://shillehtek.com/products/shillehtek-6mm-650nm-5mw-red-laser-diode-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-6mm-650nm-5mw-red-laser-diode-module-manual
// More examples: https://github.com/shillehtek/examples
//

// Laser Diode - Blink via NPN transistor on D9
// Wiring: D9 -> 1k resistor -> NPN base
//         NPN collector -> laser GND wire
//         NPN emitter -> Arduino GND
//         Laser +5V wire -> Arduino 5V

const int laserPin = 9;

void setup() {
  pinMode(laserPin, OUTPUT);
}

void loop() {
  digitalWrite(laserPin, HIGH);   // laser ON
  delay(500);
  digitalWrite(laserPin, LOW);    // laser OFF
  delay(500);
}
