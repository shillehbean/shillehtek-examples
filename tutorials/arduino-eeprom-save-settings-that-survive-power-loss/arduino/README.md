# Arduino examples

- [`eeprom_led_state.ino`](./eeprom_led_state.ino) — Arduino sketch that toggles an LED with a pushbutton and saves/restores the LED state in EEPROM using EEPROM.update so the state survives power loss.
- [`eeprom_settings_example.ino`](./eeprom_settings_example.ino) — Arduino sketch demonstrating storing a Settings struct in EEPROM with a magic marker and boot counter, loading defaults if absent, and updating settings from Serial input (snippet is truncated).

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/arduino-eeprom-save-settings-that-survive-power-loss)  
Parts used: [Arduino Uno R3 Super Starter Kit](https://shillehtek.com/products/arduino-uno-r3-starter-kit) · [Tactile Button Kit](https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm) · [Resistor Kit](https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box) · [400-Point Breadboard](https://shillehtek.com/products/shillehtek-400-point-breadboard) · [Dupont Jumper Wires](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire)
