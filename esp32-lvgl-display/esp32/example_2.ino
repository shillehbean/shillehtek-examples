// Sets up LVGL with a TFT_eSPI draw buffer and flush callback, registers the display driver, and creates a simple centered LVGL button labeled 'Hello CYD'.
//
// Buy this module: https://shillehtek.com/products/Display
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-lvgl-2-8-inch-240x320-smart-display-with-resistive-touch-wifi-bluetooth-dev-board-manual
// More examples: https://github.com/shillehtek/examples
//

#include <lvgl.h>
#include <TFT_eSPI.h>

static const uint16_t SCREEN_W = 320;
static const uint16_t SCREEN_H = 240;

TFT_eSPI tft = TFT_eSPI();
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[SCREEN_W * 10];

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = area->x2 - area->x1 + 1;
  uint32_t h = area->y2 - area->y1 + 1;
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();
  lv_disp_flush_ready(disp);
}

void setup() {
  pinMode(21, OUTPUT); digitalWrite(21, HIGH);
  tft.begin();
  tft.setRotation(1);

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, SCREEN_W * 10);

  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = SCREEN_W;
  disp_drv.ver_res = SCREEN_H;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  lv_obj_t *btn = lv_btn_create(lv_scr_act());
  lv_obj_center(btn);
  lv_obj_t *label = lv_label_create(btn);
  lv_label_set_text(label, "Hello CYD");
}

void loop() {
  lv_timer_handler();
  delay(5);
}
