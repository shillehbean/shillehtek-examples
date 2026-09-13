// When the TinyGPS++ location is updated, print the latitude and longitude to the Serial monitor with six decimal places.
//
// Full tutorial: https://shillehtek.com/blogs/news/gps-with-arduino-neo-6m-step-by-step-tutorial-with-tinygps
// Parts used: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
// More examples: https://github.com/shillehbean/shillehtek-examples
//

if (gps.location.isUpdated()) {
  Serial.print(gps.location.lat(), 6);
  Serial.print(", ");
  Serial.println(gps.location.lng(), 6);
}
