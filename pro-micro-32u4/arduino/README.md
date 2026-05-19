# Arduino examples

- [`example_1.ino`](./example_1.ino) — Toggles the Pro Micro's built-in TX and RX LEDs (active-LOW) every 500 ms to provide a blink indicator since there's no dedicated user LED pin.
- [`example_2.ino`](./example_2.ino) — Uses a pushbutton on D2 with INPUT_PULLUP to send the string "Hello from Pro Micro!" and press Enter via the USB Keyboard HID on button press.
- [`example_3.ino`](./example_3.ino) — Acts as a simple mouse jiggler by moving the cursor one pixel right and back, then waiting 30 seconds to simulate user activity.
- [`example_4.ino`](./example_4.ino) — Scans the I2C bus (addresses 1–126) and prints any detected device addresses to the native USB Serial console to verify SDA/SCL wiring.
- [`example_5.ino`](./example_5.ino) — Implements a USB media control remote using the HID-Project library, mapping three buttons (D2/D3/D4) to Play/Pause, Next, and Previous commands.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/pro-micro-atmega32u4-5v-16mhz-presoldered-type-c-manual)  
Buy the module: https://shillehtek.com/products/manual
