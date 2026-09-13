// Implements a relay toggle callback for an LVGL button that flips a relay on GPIO32 and updates the button label between "Light ON" and "Light OFF".
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-lvgl-display-touchscreen-smart-switch-ui
// Parts used: https://shillehtek.com/products/esp32-lvgl-2-8-inch-240x320-smart-display-with-resistive-touch-wifi-bluetooth-dev-board
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/4-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int RELAY = 32;
bool relayOn = false;

static void toggle_cb(lv_event_t* e) {
  relayOn = !relayOn;
  digitalWrite(RELAY, relayOn ? HIGH : LOW);
  lv_obj_t* btn = lv_event_get_target(e);
  lv_label_set_text(lv_obj_get_child(btn, 0),
                     relayOn ? "Light ON" : "Light OFF");
}

void setup() {
  pinMode(RELAY, OUTPUT);
  // ... LVGL init from step 3 ...
  lv_obj_t* btn = lv_btn_create(lv_scr_act());
  lv_obj_set_size(btn, 200, 80);
  lv_obj_center(btn);
  lv_obj_add_event_cb(btn, toggle_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_t* lbl = lv_label_create(btn);
  lv_label_set_text(lbl, "Light OFF");
}
