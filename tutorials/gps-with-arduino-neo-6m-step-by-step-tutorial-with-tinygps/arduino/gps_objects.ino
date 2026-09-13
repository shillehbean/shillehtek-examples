// Instantiate a SoftwareSerial object on pins 2 and 3 and create a TinyGPSPlus parser object to hold parsed GPS data.
//
// Full tutorial: https://shillehtek.com/blogs/news/gps-with-arduino-neo-6m-step-by-step-tutorial-with-tinygps
// Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
// More examples: https://github.com/shillehbean/shillehtek-examples
//

SoftwareSerial serial_connection(2, 3);
TinyGPSPlus gps;
