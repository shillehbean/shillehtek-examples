// Step-by-step instructions to configure the W1209: set the temperature to 37.5°C, choose cooling mode (heater ON below setpoint), set 0.5°C hysteresis, wire the heating pad through K0–K1, and observe the relay LED behavior at 37°C/37.5°C thresholds.
//
// Buy this module: https://shillehtek.com/products/w1209-12v-digital-temperature-controller-thermostat-switch-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/w1209-12v-digital-temperature-controller-thermostat-switch-module-manual
// More examples: https://github.com/shillehtek/examples
//

1. Power up the W1209 with 12V DC.
2. Tap SET briefly. Display shows current setpoint.
3. Press + or − to set 37.5°C. Press SET to save.
4. Hold SET ~3 seconds to enter parameter menu.
5. + to scroll to P0. Press SET. Use + or − to choose "C" (cooling=OFF means heater stays on
   below setpoint). Press SET.
6. + to scroll to P1. Press SET. Set hysteresis to 0.5°C. Press SET.
7. Hold SET 3 seconds to exit menu.
8. Wire heating pad through K0-K1.
9. Watch the green relay LED — it turns on when temperature drops below 37°C
   and turns off when it rises above 37.5°C (37 + 0.5 hysteresis).
