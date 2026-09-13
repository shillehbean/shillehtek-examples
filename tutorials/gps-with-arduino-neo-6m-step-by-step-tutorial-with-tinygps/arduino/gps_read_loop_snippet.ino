// Read available bytes from the GPS module's serial connection and feed each character into the TinyGPS++ parser.
//
// Full tutorial: https://shillehtek.com/blogs/news/gps-with-arduino-neo-6m-step-by-step-tutorial-with-tinygps
// Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
// More examples: https://github.com/shillehbean/shillehtek-examples
//

while (serial_connection.available()) {
  gps.encode(serial_connection.read());
}
