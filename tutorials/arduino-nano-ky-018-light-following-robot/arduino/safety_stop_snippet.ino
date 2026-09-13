// Small snippet to stop both motors when ambient light is below a defined threshold (safety/idle behavior).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ky-018-light-following-robot
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/photoresistor-light-sensor-ky-018-arduino-esp32
//             https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
// More examples: https://github.com/shillehbean/shillehtek-examples
//

if (L < 100 && R < 100) {
  // too dark, stop
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
  return;
}
