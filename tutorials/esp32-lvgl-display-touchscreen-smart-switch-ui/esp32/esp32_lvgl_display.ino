// Initializes LVGL with TFT_eSPI, implements the display flush callback, registers the LVGL display driver, and creates a centered button labeled "Hello LVGL!".
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-lvgl-display-touchscreen-smart-switch-ui
// Parts used: https://shillehtek.com/products/esp32-lvgl-2-8-inch-240x320-smart-display-with-resistive-touch-wifi-bluetooth-dev-board
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/4-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <lvgl.h>
#include <TFT_eSPI.h>
#include "touch.h"   // XPT2046 helper

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[240 * 10];

void my_disp_flush(lv_disp_drv_t *d, const lv_area_t *a, lv_color_t *p) {
  tft.startWrite();
  tft.setAddrWindow(a->x1, a->y1, a->x2-a->x1+1, a->y2-a->y1+1);
  tft.pushColors((uint16_t*)&p->full, (a->x2-a->x1+1)*(a->y2-a->y1+1), true);
  tft.endWrite();
  lv_disp_flush_ready(d);
}

void setup() {
  tft.begin(); tft.setRotation(1);
  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 240*10);
  static lv_disp_drv_t drv;
  lv_disp_drv_init(&drv);
  drv.flush_cb = my_disp_flush;
  drv.hor_res = 320; drv.ver_res = 240;
  drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&drv);

  lv_obj_t* btn = lv_btn_create(lv_scr_act());
  lv_obj_center(btn);
  lv_obj_t* lbl = lv_label_create(btn);
  lv_label_set_text(lbl, "Hello LVGL!");
}
void loop() { lv_timer_handler(); delay(5); }
