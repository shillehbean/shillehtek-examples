# Arduino examples

- [`gps_includes.ino`](./gps_includes.ino) — Include the TinyGPS++ and SoftwareSerial libraries needed to parse GPS NMEA sentences and create a software serial port for the module.
- [`gps_objects.ino`](./gps_objects.ino) — Instantiate a SoftwareSerial object on pins 2 and 3 and create a TinyGPSPlus parser object to hold parsed GPS data.
- [`gps_setup.ino`](./gps_setup.ino) — Initialize the hardware Serial and the SoftwareSerial at 9600 baud and print a startup message to the Serial monitor.
- [`gps_read_loop_snippet.ino`](./gps_read_loop_snippet.ino) — Read available bytes from the GPS module's serial connection and feed each character into the TinyGPS++ parser.
- [`gps_print_coords_snippet.ino`](./gps_print_coords_snippet.ino) — When the TinyGPS++ location is updated, print the latitude and longitude to the Serial monitor with six decimal places.
- [`gps_neo6m_tinygps.ino`](./gps_neo6m_tinygps.ino) — Complete Arduino sketch that initializes serial ports, continuously reads GPS data, parses it with TinyGPS++ and prints updated latitude/longitude to Serial.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/gps-with-arduino-neo-6m-step-by-step-tutorial-with-tinygps)  
Parts used: [GT-U7 NEO-6M GPS Module Pre-Soldered for Arduino & Raspberry Pi](https://shillehtek.com/products/gt-u7-gps-module-presoldered-1)
