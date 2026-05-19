// Acts as a simple mouse jiggler by moving the cursor one pixel right and back, then waiting 30 seconds to simulate user activity.
//
// Buy this module: https://shillehtek.com/products/manual
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pro-micro-atmega32u4-5v-16mhz-presoldered-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Classic "mouse jiggler" — moves the cursor a pixel every
// 30 seconds so your computer thinks you're still at it.

#include <Mouse.h>

void setup() {
  Mouse.begin();
}

void loop() {
  Mouse.move(1, 0, 0);
  delay(100);
  Mouse.move(-1, 0, 0);
  delay(30000);  // 30 seconds
}
