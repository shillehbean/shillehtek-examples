// MicroPython for ESP32 that reads NMEA RMC/GNRMC sentences from UART2 (GPIO16/17) and prints the NMEA lines to the REPL.
//
// Buy this module: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gt-u7-gps-module-presoldered-1-manual
// More examples: https://github.com/shillehtek/examples
//

# GT-U7 GPS on ESP32 (MicroPython)
# Wiring: VCC->5V, GND->GND, GT-U7 TXD->GPIO16, GT-U7 RXD->GPIO17

from machine import UART
import time

uart = UART(2, baudrate=9600, tx=17, rx=16)
print("GT-U7 GPS: reading from UART2...")

while True:
    if uart.any():
        try:
            line = uart.readline()
            if line:
                sentence = line.decode('ascii', 'ignore').strip()
                if sentence.startswith('$GPRMC') or sentence.startswith('$GNRMC'):
                    print(sentence)
        except Exception as e:
            print("Parse error:", e)
    time.sleep_ms(100)
