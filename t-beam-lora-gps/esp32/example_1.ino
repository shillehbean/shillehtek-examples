// Power the NEO-6M via the AXP PMU, read NMEA sentences from the GPS over Serial1, parse them with TinyGPSPlus, and print latitude, longitude, and satellite count to the USB serial console.
//
// Buy this module: https://shillehtek.com/products/esp32-tbeam-lora-915mhz-neo6m-gps
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-tbeam-lora-915mhz-neo6m-gps-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// T-Beam v1.1 - read NEO-6M GPS and print position
// Libraries: TinyGPSPlus, XPowersLib (both in Library Manager)

#include <TinyGPSPlus.h>
#include <Wire.h>
#include <XPowersLib.h>

TinyGPSPlus gps;
XPowersAXP192 pmu;   // v1.2 boards: use XPowersAXP2101 instead

void setup() {
  Serial.begin(115200);

  // 1) Wake the PMU and switch on the GPS power rail (LDO3, 3.3V)
  Wire.begin(21, 22);
  pmu.begin(Wire, AXP192_SLAVE_ADDRESS, 21, 22);
  pmu.setLDO3Voltage(3300);
  pmu.enableLDO3();

  // 2) GPS UART: RX=34, TX=12, 9600 baud
  Serial1.begin(9600, SERIAL_8N1, 34, 12);
  Serial.println("Waiting for GPS fix (go outdoors)...");
}

void loop() {
  while (Serial1.available()) {
    gps.encode(Serial1.read());
  }
  if (gps.location.isUpdated()) {
    Serial.print("Lat: ");  Serial.print(gps.location.lat(), 6);
    Serial.print("  Lng: "); Serial.print(gps.location.lng(), 6);
    Serial.print("  Sats: "); Serial.println(gps.satellites.value());
  }
}
