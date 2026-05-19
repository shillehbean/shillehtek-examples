# Calculate the input current required by a boost converter given output voltage/current and efficiency, with example numeric calculations for common battery-to-output scenarios.
#
# Buy this module: https://shillehtek.com/products/mt3608-dc-dc-step-up-boost-converter-2a-adjustable-power-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mt3608-dc-dc-step-up-boost-converter-2a-adjustable-power-module-manual
# More examples: https://github.com/shillehtek/examples
#

Power balance for a boost converter (assuming 90% efficiency):

  V_in × I_in × 0.9 = V_out × I_out

Solve for input current:

  I_in = (V_out × I_out) / (V_in × 0.9)

Examples:
  3.7V LiPo → 5V at 1A:  I_in = 5 × 1 / (3.7 × 0.9) = ~1.5A from battery
  3.7V LiPo → 12V at 0.5A: I_in = 12 × 0.5 / (3.7 × 0.9) = ~1.8A
  6V (4xAA) → 9V at 0.5A: I_in = 9 × 0.5 / (6 × 0.9) = ~0.83A

Always size your input source for the calculated input current.
