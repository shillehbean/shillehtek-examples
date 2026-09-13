// Maps a raw analog sensor reading to a moisture percentage using calibrated wet and dry bounds (using Arduino's map-style logic).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-soil-moisture-sensor-pick-capacitive
// Parts used: https://shillehtek.com/products/capacitive-soil-moisture-sensor-v1-2
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

moisture% = map(reading, wet_min, dry_max, 100, 0)
