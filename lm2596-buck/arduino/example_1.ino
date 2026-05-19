// Hands-on procedure for powering the module, switching the display to show output, adjusting the multi-turn trim pot to set the output voltage, and wiring the load; also notes short/medium/long button-press behaviors.
//
// Buy this module: https://shillehtek.com/products/shillehtek-lm2596-dc-dc-adjustable-step-down-power-supply-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-lm2596-dc-dc-adjustable-step-down-power-supply-module-manual
// More examples: https://github.com/shillehtek/examples
//

1. Connect IN+ and IN- to your DC source (4-40V).
   The display lights up and shows the input voltage.

2. Short-press the function button.
   The display switches between input ("IN") and output ("OUT") readings.
   Leave it on OUT.

3. Use a small flathead screwdriver on the multi-turn trim pot.
   - Clockwise   = step UP voltage
   - Counter-CW  = step DOWN voltage
   The display updates live.

4. Once you see your target voltage on OUT, disconnect input,
   then wire the load to OUT+ / OUT- and re-power.

Optional: medium-press the button to enter fine-tune mode
(adjusts the displayed value by 0.01V offset for calibration).
Long-press the button to enter low-power "display off" state.
