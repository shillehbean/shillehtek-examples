// Configures the ESP32 I2S peripheral to receive 32-bit samples from the INMP441, computes a shifted average amplitude from the captured buffer, and prints the result over Serial.
//
// Buy this module: https://shillehtek.com/products/inmp441-i2s-omnidirectional-microphone-module-with-soldering
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/inmp441-i2s-omnidirectional-microphone-module-with-soldering-manual
// More examples: https://github.com/shillehtek/examples
//

#include <driver/i2s.h>

#define I2S_WS  15
#define I2S_SD  32
#define I2S_SCK 14
#define I2S_PORT I2S_NUM_0
#define BUFFER_LEN 1024

int32_t sBuffer[BUFFER_LEN];

void i2s_install() {
  const i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = BUFFER_LEN,
    .use_apll = false
  };
  i2s_driver_install(I2S_PORT, &cfg, 0, NULL);
}

void i2s_setpin() {
  const i2s_pin_config_t pins = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };
  i2s_set_pin(I2S_PORT, &pins);
}

void setup() {
  Serial.begin(115200);
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);
}

void loop() {
  size_t bytesIn = 0;
  i2s_read(I2S_PORT, &sBuffer, sizeof(sBuffer), &bytesIn, portMAX_DELAY);
  long sum = 0;
  int n = bytesIn / 4;
  for (int i = 0; i < n; i++) sum += (sBuffer[i] >> 14);  // shift to 18-bit usable
  Serial.println(sum / n);
}
