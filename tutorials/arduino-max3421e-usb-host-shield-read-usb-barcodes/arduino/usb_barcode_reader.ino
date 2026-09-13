// Initializes the USB host and a HID keyboard parser to read characters from a USB barcode scanner and print them to Serial, using Enter (key 0x28) to end each barcode line.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-max3421e-usb-host-shield-read-usb-barcodes
// Parts used: https://shillehtek.com/products/mini-usb-host-shield-2-0-adk-module-max3421e-for-arduino-pro-mini
//             https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-presoldered-micro-usb
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <hidboot.h>
#include <usbhub.h>

USB Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> kbd(&Usb);

class KbdRptParser : public KeyboardReportParser {
  void OnKeyDown(uint8_t mod, uint8_t key) override {
    uint8_t c = OemToAscii(mod, key);
    if (c) Serial.write(c);
    if (key == 0x28) Serial.println();   // Enter ends a barcode
  }
};
KbdRptParser P;

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) { Serial.println("USB init failed"); while (1); }
  kbd.SetReportParser(0, &P);
}

void loop() { Usb.Task(); }
