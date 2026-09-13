// Initialize the hardware Serial and the SoftwareSerial at 9600 baud and print a startup message to the Serial monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/gps-with-arduino-neo-6m-step-by-step-tutorial-with-tinygps
// Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void setup() {
  Serial.begin(9600);
  serial_connection.begin(9600);
  Serial.println("GPS Start");
}
