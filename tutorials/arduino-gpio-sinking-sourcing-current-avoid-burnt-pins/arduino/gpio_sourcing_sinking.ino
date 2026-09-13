// Shows how to configure a GPIO pin and drive it high or low to illustrate sourcing (pin -> LED -> GND) and sinking (+5V -> LED -> pin) behaviors with an LED on pin 13.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-gpio-sinking-sourcing-current-avoid-burnt-pins
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// SOURCING: pin -> LED -> resistor -> GND
//          digitalWrite(13, HIGH)  -> LED ON
//          digitalWrite(13, LOW)   -> LED OFF
pinMode(13, OUTPUT);
digitalWrite(13, HIGH);

// SINKING:  +5V -> resistor -> LED -> pin
//          digitalWrite(13, LOW)   -> LED ON
//          digitalWrite(13, HIGH)  -> LED OFF
pinMode(13, OUTPUT);
digitalWrite(13, LOW);
