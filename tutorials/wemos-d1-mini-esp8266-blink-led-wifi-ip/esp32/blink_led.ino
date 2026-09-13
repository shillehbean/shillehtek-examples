// Blink the Wemos D1 Mini built-in LED with a 300 ms on/off cycle (D4 LED is active LOW).
//
// Full tutorial: https://shillehtek.com/blogs/news/wemos-d1-mini-esp8266-blink-led-wifi-ip
// Parts used: https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);   // LOW = on (active-LOW LED on D4)
  delay(300);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);
}
